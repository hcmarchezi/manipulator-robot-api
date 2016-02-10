#include "matrix.h"

namespace PDC {

Matrix::Matrix()
{
}

void Matrix::SetIdentity(double (*matrix)[4][4])
{
    (*matrix)[0][0] = (*matrix)[1][1] = (*matrix)[2][2] = (*matrix)[3][3] = 1.0;
    (*matrix)[0][1] = (*matrix)[0][2] = (*matrix)[0][3] = 0.0;
    (*matrix)[1][0] = (*matrix)[1][2] = (*matrix)[1][3] = 0.0;
    (*matrix)[2][0] = (*matrix)[2][1] = (*matrix)[2][3] = 0.0;
    (*matrix)[3][0] = (*matrix)[3][1] = (*matrix)[3][2] = 0.0;
}

} // namespace PDC
