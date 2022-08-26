#include <stdio.h>
#include "additional_functions.h"


/// \brief                      Checks whether the float type numbers are equal
/// \param[in]  n               The number that is being comparedh
/// \param[in]  equivalent      The number to compare with
/// \return                     'True' - if the float type numbers are equal, 'false' - otherwise
bool isEqFloat(float n, float equivalent)
{
    const float Epsilon = 1e-6;

    return n <= Epsilon + equivalent && n >= -Epsilon + equivalent;
}

/// \brief  To clears the buffer
void clearBuffer(void)
{
    int c = 0;
    while ((c = getchar()) != '\n');
}
