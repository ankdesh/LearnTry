if [ -z "$1" ]
  then
    echo "Usage emit-ll.sh <name of folder in examples>"
    exit 1
fi

dir=$(pwd)/../examples/${1}

cmd="opt -S -loop-vectorize -force-vector-width=16 -o $dir/$1-vect.ll $dir/$1.ll"

echo Executing... ${cmd}
eval $cmd 
