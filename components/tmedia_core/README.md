# Description
- Maintainer: Lu Chongzhi

# Code style
- astyle --style=ansi --convert-tabs --align-pointer=name --max-code-length=120 --break-after-logical -p -H -U -n %f
- More c++ code styles refer to: https://ata.alibaba-inc.com/articles/75718
- To find Chinese characters in source code files:
    find ./ -name ".c" -o -name ".h" -o -name "*.cpp" | env LANG=LC_ALL xargs -i grep -nP "[\xB0\xA1-\xF7\xFE]+" {}
