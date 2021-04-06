if [ -z "$1" ]
  then
    echo "Usage opt-extract-loop.sh <name of folder in examples>"
    exit 1
fi

dir=$(pwd)/../examples/${1}

cmd="opt -S -loop-extract-single -debug -o $dir/$1-loop-extract.ll $dir/$1.ll"

echo Executing... ${cmd}
eval $cmd 
