if [ -z "$1" ]
  then
    echo "Usage emit-ll.sh <name of folder in examples>"
    exit 1
fi

dir=$(pwd)/../examples/${1}

cmd="clang -c -S -emit-llvm -O1 -mllvm -debug-pass=Arguments  -Rpass-analysis=loop-vectorize -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -o $dir/$1.ll ${dir}/${1}.c"

echo Executing... ${cmd}
eval $cmd 
