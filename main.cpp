#include <fstream>
#include <iostream>
#include <fftw3.h>
#include <math.h>
#include <vector>

using namespace std;



int main()
{
    fftw_complex *out;
    double *in, *result;
    fftw_plan p;
    double g;
    int amountOfSamplesPerSymbol = 99;
    int flag = 0;
    //int firstByteToRead = 0;
    int borderWindowNumber = 2;
    vector<int> dataArray;


    in = (double*) fftw_malloc(sizeof(double) * amountOfSamplesPerSymbol);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * amountOfSamplesPerSymbol / 2 +1);
    result = (double*) fftw_malloc(sizeof(double) * amountOfSamplesPerSymbol / 2 +1);


    ifstream fin("/root/cpp/fft/signal2.bin", ios::binary);
    while (fin.read(reinterpret_cast<char*>(&g), sizeof(double))) {
        in[flag] = g;
        flag++;
        if(amountOfSamplesPerSymbol == flag){

            flag = 0;
            p = fftw_plan_dft_r2c_1d(amountOfSamplesPerSymbol, in, out, FFTW_ESTIMATE);
            fftw_execute(p); /* repeat as needed */
            fftw_destroy_plan(p);

            int maxOut = 0;
            int freqOfCurrentWindow = 0;
            for(int i = 1; i<= amountOfSamplesPerSymbol/2; i++) { //from 1 because first value isn't needed
                result[i] = out[i][0] * out[i][0] + out[i][1] * out[i][1];

                if(result[i] > maxOut) {
                    maxOut = result[i];
                    freqOfCurrentWindow = i;
                }
            }

            if (freqOfCurrentWindow <= borderWindowNumber) {
                dataArray.push_back(1);
            } else {
                dataArray.push_back(0);
            }

            fftw_free(out);
            free(in);

            in = (double*) fftw_malloc(sizeof(double) * amountOfSamplesPerSymbol);
            out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * amountOfSamplesPerSymbol / 2 +1);
        }

    }

    cout << "@@@@@@@@@@  after transform @@@@@@@@@"<< endl;


    for(int i = 0; i < dataArray.size(); i++){
        cout << dataArray.at(i) << ",";
    }

    return 0;
}






