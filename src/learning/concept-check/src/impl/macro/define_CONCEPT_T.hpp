#include "../integral_immutable.hpp"

#ifndef CONCEPT_T
# define CONCEPT_T inline constexpr const bool
#endif

//The following code is facility for creating concept quickly.

/*
 * The begin of different forms(class, function, value) of concept.
 * They should be used with DEF_CONCEPT_1 / DEF_CONCEPT_2.
 * Eg:
 *    template <class T> struct FUNC_NAME ##_t: bool_immutable<COND> {}
 *    template <class T> CONCEPT_T FUNC_NAME ## _v {...}
 * Using the following facility here, you can write:
 *    DEF_CONCEPT_1(FUNC_NAME, ...(COND), DEF_CONCEPT_T);
 *    DEF_CONCEPT_1(FUNC_NAME ## _v, ...(COND), DEF_CONCEPT_V);
 */
#ifndef DEF_CONCEPT_V
# define DEF_CONCEPT_V(NAME, COND, ...) CONCEPT_T NAME { COND }
#endif

#ifndef DEF_CONCEPT_T
# define DEF_CONCEPT_T(NAME, COND, ...) struct NAME : concept_check::bool_immutable< COND > {};
#endif
/* The end. */

/*
 * The begin of wrapper.
 * Wrappers enables one to write one form(class, value) of concept wrappee over another form(function, class, value).
 * Eg.
 *    namespace impl {
 *    DEF_CONCEPT_1(FUNC_NAME, ...(COND), DEF_CONCEPT_F)
 *    template <class T> CONCEPT_T FUNC_NAME ## _v { FUNC_NAME <T>()};
 *    }
 *    using impl:: FUNC_NAME ## _v;
 * Using the wrapper here, it will be:
 *    namespace impl {
 *    DEF_CONCEPT_1(FUNC_NAME. , DEF_CONCEPT_V_WRAPPER)
 *    DEF_CONCEPT_1(FUNC_NAME ## _v, FUNC_NAME <T>(), DEF_CONCEPT_V);
 *    }
 */
#ifndef DEF_CONCEPT_V_WRAPPER_FOR_F
# define DEF_CONCEPT_V_WRAPPER_FOR_F(FUNC_NAME, COND, ...) DEF_CONCEPT_V( FUNC_NAME ## _v, (FUNC_NAME < __VA_ARGS__ >()))
#endif

#ifndef DEF_CONCEPT_T_WRAPPER_FOR_F
#define DEF_CONCEPT_T_WRAPPER_FOR_F(FUNC_NAME, COND, ...) DEF_CONCEPT_T(FUNC_NAME ##_t, (FUNC_NAME < __VA_ARGS__ >()))
#endif
/* The end. */

#ifndef DEF_CONCEPT_1
# define DEF_CONCEPT_1(NAME, COND, MACRO) template <class T> MACRO(NAME, COND, T)
#endif

#ifndef DEF_CONCEPT_2
# define DEF_CONCEPT_2(NAME, COND, MACRO) template <class T1, class T2> MACRO(NAME, COND, T1, T2)
#endif
