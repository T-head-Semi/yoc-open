#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <FLAC/stream_decoder.h>
#include "test_data.h"
//#include "index_entry_flac-2s.h"

#define FLAC_BUFFER_SIZE 1024 * 8 // 8 KB FLAC 输入数据缓冲区大小
#define PCM_BUFFER_SIZE 1024 * 150   // 150 KB PCM 输出数据缓冲区大小
static uint8_t pcm_out[PCM_BUFFER_SIZE * sizeof(int16_t)];

typedef struct {
   union  {
     int16_t* data_s16;
     int32_t* data_s32;
   };
} pcm_out_data;

void* __dso_handle = 0;
static int g_audio_depath = 0;

typedef struct {
    uint8_t *flac_data;          // 输入的 FLAC 数据数组
    size_t flac_data_size;       // FLAC 数据的大小
    size_t flac_data_pos;        // 当前读取的位置
    pcm_out_data pcm_data;           // 输出的 PCM 数据数组
    size_t pcm_data_size;        // PCM 数据的大小 
} AudioBuffer;

typedef struct {
    unsigned sample_rate;        // 音频采样率
    unsigned channels;           // 音频通道数
    AudioBuffer *output;         // 输出缓冲区
} FLACDecoderContext;

// 读取回调
static FLAC__StreamDecoderReadStatus read_callback(
    const FLAC__StreamDecoder *decoder,
    FLAC__byte buffer[],
    size_t *bytes,
    void *client_data) {
    
    FLACDecoderContext *context = (FLACDecoderContext *)client_data;
    AudioBuffer *audio_buffer = context->output;

    // 从 flac_data 中读取数据
    size_t available_bytes = audio_buffer->flac_data_size - audio_buffer->flac_data_pos;
    if (available_bytes == 0) {
        *bytes = 0; // 没有数据可读取
        return FLAC__STREAM_DECODER_READ_STATUS_END_OF_STREAM;
    }

    *bytes = (*bytes > available_bytes) ? available_bytes : *bytes; // 确保不会超出可用字节数
    memcpy(buffer, audio_buffer->flac_data + audio_buffer->flac_data_pos, *bytes);
    audio_buffer->flac_data_pos += *bytes; // 更新读取位置

    return FLAC__STREAM_DECODER_READ_STATUS_CONTINUE;
}

// Seek 回调（可选，根据需要实现）
static FLAC__StreamDecoderSeekStatus seek_callback(
    const FLAC__StreamDecoder *decoder,
    FLAC__uint64 absolute_byte_offset,
    void *client_data) {
    // 在此处实现 seek 功能
    return FLAC__STREAM_DECODER_SEEK_STATUS_OK;
}

// Tell 回调（可选，根据需要实现）
static FLAC__StreamDecoderTellStatus tell_callback(
    const FLAC__StreamDecoder *decoder,
    FLAC__uint64 *absolute_byte_offset,
    void *client_data) {

    FLACDecoderContext *context = (FLACDecoderContext *)client_data;

    // 设置当前读取位置
    *absolute_byte_offset = context->output->flac_data_pos;

    return FLAC__STREAM_DECODER_TELL_STATUS_OK; // 返回状态，表示成功
}

// Length 回调（可选，根据需要实现）
static FLAC__StreamDecoderLengthStatus length_callback(
    const FLAC__StreamDecoder *decoder,
    FLAC__uint64 *length,
    void *client_data) {

    FLACDecoderContext *context = (FLACDecoderContext *)client_data;

    // 设置当前 flac 数据的大小
    *length = context->output->flac_data_size;

    return FLAC__STREAM_DECODER_LENGTH_STATUS_OK; // 返回成功状态
}


// EOF 回调（可选，根据需要实现）
static FLAC__bool eof_callback(const FLAC__StreamDecoder *decoder, void *client_data) {
    return ((FLACDecoderContext *)client_data)->output->flac_data_pos >= 
           ((FLACDecoderContext *)client_data)->output->flac_data_size;
}


// 写回调
static FLAC__StreamDecoderWriteStatus write_callback(
    const FLAC__StreamDecoder *decoder,
    const FLAC__Frame *frame,
    const FLAC__int32 *const buffer[],
    void *client_data) {

    FLACDecoderContext *context = (FLACDecoderContext *)client_data;
    AudioBuffer *audio_buffer = context->output;

    // 检查总样本数和采样位数
    
    if(g_audio_depath == 16) {
            // 将 PCM 样本写入 PCM 数组
        for (size_t i = 0; i < frame->header.blocksize; i++) {
            // 先处理左声道
            if ((audio_buffer->pcm_data_size << 1) < sizeof(pcm_out)) {
                int16_t left_sample = (FLAC__int16)buffer[0][i]; 
                audio_buffer->pcm_data.data_s16[audio_buffer->pcm_data_size++] = left_sample;
            } else {
                printf("PCM buffer overflow\n");
                return FLAC__STREAM_DECODER_WRITE_STATUS_ABORT; // 或者直接返回
            }

            // 处理右声道
            if(frame->header.channels == 2) {
                if ((audio_buffer->pcm_data_size << 1 )< sizeof(pcm_out)) {
                    int16_t right_sample = (FLAC__int16)buffer[1][i];
                    audio_buffer->pcm_data.data_s16[audio_buffer->pcm_data_size++] = right_sample;
                } else {
                    printf("PCM buffer overflow\n");
                    return FLAC__STREAM_DECODER_WRITE_STATUS_ABORT; // 或者直接返回
                }
            }

            //printf("%04x %04x",(FLAC__int16)buffer[0][i],(FLAC__int16)buffer[1][i]);
        }
    }
    return FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE;
}

// 元数据回调
static void metadata_callback(
    const FLAC__StreamDecoder *decoder,
    const FLAC__StreamMetadata *metadata,
    void *client_data) {
    
    if (metadata->type == FLAC__METADATA_TYPE_STREAMINFO) {
        FLACDecoderContext *context = (FLACDecoderContext *)client_data;
        context->sample_rate = metadata->data.stream_info.sample_rate;
        context->channels = metadata->data.stream_info.channels;
        //printf("Sample Rate: %u, Channels: %u\n", context->sample_rate, context->channels);
    }
}

// 错误回调
static void error_callback(
    const FLAC__StreamDecoder *decoder,
    FLAC__StreamDecoderErrorStatus status,
    void *client_data) {
    printf("Error: %d\n", status);
}

static int get_audio_depath(char* str)
{
   if(!memcmp("s16", str, strlen(str))) {
      return 16;
   } else if(!memcmp("s32", str, strlen(str))) {
      return 32;
   } else {
      return -1;
   }
}

void* flac_test() {
    // 假设你已经将 FLAC 数据填充到以下数组中
    //uint8_t flac_data[FLAC_BUFFER_SIZE]; // 你要管理这个数组并填充数据
    size_t flac_data_size = sizeof(flac_audio_data);/* 填入数据大小 */; // 设置实际数据大小

    // 创建解码器
    FLAC__StreamDecoder *decoder = FLAC__stream_decoder_new();
    if (!decoder) {
        printf("Failed to create FLAC decoder\n");
        return NULL;
    }

    // 创建 PCM 输出缓冲区
    AudioBuffer audio_buffer = { (uint8_t*)flac_audio_data, flac_data_size, 0, (int16_t *)pcm_out, 0 };

	/* gdb dump memory's pcm format
	 * Signed 16-bit PCM 
	 * little-endian
	 * 2 channel
	 */
	g_audio_info.out_data = (char*)audio_buffer.pcm_data.data_s16;
    g_audio_info.out_data_len = 0;
    g_audio_depath = get_audio_depath(g_audio_info.depth);
    if(g_audio_depath <= 0) {
        printf("get audio depath faild\n");
        return NULL;
    }

    if(g_audio_depath != 16) {
        printf("test case only support s16\n");
        return NULL;
    }

	memset(g_audio_info.out_data, 0, g_audio_info.out_data_len);

    // 设置上下文
    FLACDecoderContext context = { .sample_rate = 0, .channels = 0, .output = &audio_buffer};

    // 初始化解码器并设置回调
    FLAC__StreamDecoderInitStatus init_status = FLAC__stream_decoder_init_stream(
        decoder,
        read_callback,
        seek_callback,
        tell_callback,
        length_callback,
        eof_callback,
        write_callback,
        metadata_callback,
        error_callback,
        &context
    );

    if (init_status != FLAC__STREAM_DECODER_INIT_STATUS_OK) {
        printf("Failed to initialize decoder: %d\n", init_status);
        //free(audio_buffer.pcm_data);
        FLAC__stream_decoder_delete(decoder);
        return NULL;
    }

    // 开始解码
    while (FLAC__stream_decoder_get_state(decoder) != FLAC__STREAM_DECODER_END_OF_STREAM) {
        if (FLAC__stream_decoder_process_single(decoder) != true) {
            break; // 处理出错或完成后退出
        }
    }
    

    g_audio_info.out_data_len = audio_buffer.pcm_data_size << 1;

    // 打印 PCM 数据
	// printf("pcm_data_size:%d\n", audio_buffer.pcm_data_size);
    // for (size_t i = 0; i < audio_buffer.pcm_data_size; i++) {
    //     //printf("%08x\n", audio_buffer.pcm_data[i]); // 这里打印 PCM 数据
	// 	printf("%04x\n", (uint16_t)(audio_buffer.pcm_data[i] & 0xFFFF)); // 打印为无符号十六进制
    // }

    // 清理
    FLAC__stream_decoder_finish(decoder);
    FLAC__stream_decoder_delete(decoder);
    return &g_audio_info;
}
