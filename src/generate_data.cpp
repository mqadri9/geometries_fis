#include "cnpy.h"
#include <complex>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include "generate_data.h"


int main()
{
    /*
    cnpy::NpyArray pFIS_stack = cnpy::npy_load("../python_src/FFS_stack.npy");
    string row = to_string(pFIS_stack.shape[0]);
    string col = to_string(pFIS_stack.shape[1]);
    //int row=1;
    cout << pFIS_stack.shape[0] << endl;
    cout << pFIS_stack.shape[1] << endl;
    */
    FA arr1 = {} ; 
    load_data_FFS(&FFS_stack);

    load_data_FIS_forward(&pFIS_stack);
    load_data_FIS_backward(&pFIS_stack);

    

}
