# fft
do poprawnego dzialania programu trzeba podlinkowac biblioteke fftw, w tym celu:
wejsc do folderu fftw-3.costam
./configure
make
make install
 po tym biblioteka ta zostanie zainstalowana gdzies w sysytemowej sciezce u mnie 
/usr/lib/x86_64-linux-gnu/libfftw3.a
nastepnie trzeba w podlinkowac ta scizke do projektu 
w code blocks: project->build options->linker settings-> add

to wszystko, po tym powinno smigac

