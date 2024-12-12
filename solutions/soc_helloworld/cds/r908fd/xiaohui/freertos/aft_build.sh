
#!/bin/sh

echo "I am in CDS post build."
OBJCOPY=riscv64-unknown-elf-objcopy
OBJDUMP=riscv64-unknown-elf-objdump
ELF_NAME="${PWD}/$1.elf"
MAP_NAME="${PWD}/yoc.map"
SOLUTION_PATH=$2
BOARD_PATH=$3
CHIP_PATH=$4
# echo $ELF_NAME
# echo $SOLUTION_PATH
# echo $BOARD_PATH
# echo $CHIP_PATH
$OBJCOPY -O binary $ELF_NAME ${SOLUTION_PATH}/yoc.bin
$OBJDUMP -d $ELF_NAME > ${SOLUTION_PATH}/yoc.asm
cp $ELF_NAME ${SOLUTION_PATH}/yoc.elf
cp $MAP_NAME ${SOLUTION_PATH}/yoc.map

export SOLUTION_PATH=$SOLUTION_PATH
export BOARD_PATH=$BOARD_PATH
export CHIP_PATH=$CHIP_PATH
export IS_IN_CDS=1

if [ -f "$BOARD_PATH/script/aft_build.sh" ];then
    cd $SOLUTION_PATH
    sh $BOARD_PATH/script/aft_build.sh
fi
