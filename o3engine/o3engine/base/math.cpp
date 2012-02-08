#include "./math.hpp"


namespace o3engine
{
    namespace math
    {
        Quaternion randomQuaternion()
        {
            // Create a random quaternion
            Quaternion tmp_q(randomReal(2.0) - 1.0, randomReal(2.0) - 1.0, randomReal(2.0) - 1.0, randomReal(2.0) - 1.0);
            // Normalize it to show a valid orientation without scaling
            tmp_q.normalize();
            return tmp_q;
        }
    }
}
