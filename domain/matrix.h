#ifndef PDC_MATRIX_H
#define PDC_MATRIX_H

namespace PDC {

class Matrix
{
public:
    static void SetIdentity(double (*matrix)[4][4]);
    //static void SetValues(double (*matrix)[4][4], const double* li)

private:
    Matrix();
};

} // namespace PDC

#endif // PDC_MATRIX_H
