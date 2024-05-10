gcc main.c -lm -o main
if [ $? -eq 0 ]; then
    ./main
    if [ "$(uname)" == "Darwin" ] || [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
        rm main
    elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW32_NT" ] || [ "$(expr substr $(uname -s) 1 10)" == "MINGW64_NT" ]; then
        del main
    fi
else
    echo "Compilation failed"
fi
