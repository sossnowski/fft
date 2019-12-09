#include <fstream>
#include <iostream>
#include <fftw3.h>

using namespace std;

int main()
{
    int N = 20;
    fftw_complex *out;
    double *in;
    fftw_plan p;
    double g;
    int flag = 0;

    in = (double*) fftw_malloc(sizeof(double) * N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);


    ifstream fin("/root/cpp/fft/signal.bin", ios::binary);
    while (fin.read(reinterpret_cast<char*>(&g), sizeof(double))) {
        in[flag] = g;
        cout << in[flag] << '\n';
        flag++;
        if(flag == N)
            break;
    }

    cout << "@@@@@@@@@@  after transform @@@@@@@@@"<< endl;

    p = fftw_plan_dft_r2c_1d(N, in, out, FFTW_ESTIMATE);

    fftw_execute(p); /* repeat as needed */


    for(int i = 0; i<= N/2; i++) {
        cout << out[i][0] << " " << out[i][1] << " i" <<endl;
    }


    fftw_destroy_plan(p);
    fftw_free(in); fftw_free(out);

    return 0;
}

