#include <functional>

const unsigned MODULUS = 1000000007;

template <long long N, long long... Args>
struct Sum {
    static const long long value =
        (Sum<N>::value + Sum<Args...>::value) % MODULUS;
};

template <long long N>
struct Sum<N> {
    static const long long value = N % MODULUS;
};

template <long long I, long long J, long long M, bool isEven>
struct CanChangeState : std::conditional<I & J & 1, Sum<0>,
    typename std::conditional<(I | J) & 1, typename std::conditional<isEven, CanChangeState<(I >> 1), (J >> 1), M - 1, true>, Sum<0>>::type,
                                                            CanChangeState<(I >> 1), (J >> 1), M - 1, isEven ^ 1>>::type>::type {};

template <long long I, long long J, bool isEven>
struct CanChangeState<I, J, 1, isEven> : std::conditional<I & J & 1, Sum<0>,
    typename std::conditional<(I | J) & 1, typename std::conditional<isEven, Sum<1>, Sum<0>>::type,
                                    typename std::conditional<isEven, Sum<0>, Sum<1>>::type>::type>::type {}; 

template <long long J, long long K, long long I, long long M> struct For1;

template <long long M, long long N, long long Profile>
struct AhalaiMahalai0 : For1<(1 << M) - 1, N, Profile, M> {};

template <long long M, long long Profile>
struct AhalaiMahalai0<M, 1, Profile> : Sum<(Profile == 0)> {};

template <long long J, long long K, long long I, long long M>
struct For1 : Sum<For1<J - 1, K, I, M>::value, AhalaiMahalai0<M, K - 1, J>::value * CanChangeState<J, I, M, true>::value> {};

template <long long K, long long I, long long M>
struct For1<0, K, I, M> : Sum<AhalaiMahalai0<M, K - 1, 0>::value * CanChangeState<0, I, M, true>::value> {};

template <long long M, long long N>
struct AhalaiMahalai : AhalaiMahalai0<M, N + 1, 0> {};