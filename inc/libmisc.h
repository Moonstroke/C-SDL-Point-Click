/**
 * \file libmisc.h
 * \author joH1
 *
 * \version 0.1
 *
 * \brief Some usefule types and functions definitions.
 *
 * This file contains several definitions of types and functions
 * not related to a particular type and used throughout the whole project.
*/

#ifndef LIBMISC_H
#define LIBMISC_H



/**
 * \brief A redefinition for constant strings
*/
typedef const char *str;

/**
 * \brief A convenience macro for structure needing to be padded
 */
#define padding(size) unsigned char _padding[size]


/**
 * \brief Duplicates a string.
 *
 * \note This is a personal implementation of GNU's \a strdup() function, which
 *       is (alas) not standard.
 *
 * \param[in] orig The original string to copy
 *
 * \return a \a malloc'd copy of the string
 */
str strcopy(str orig);


/**
 * \brief Concatenates two strings.
 *
 * \note This function does not modify its arguments, but returns a new string
 *       allocated with \a malloc() -- don't forget to \a free() it!
 *
 * \param[in] s1 The first string
 * \param[in] s2 The second string
 *
 * \return A \a malloc()'ed concatenation of the strings, or \c NULL if an error
 *         occurred.
 */
str strconcat(str s1, str s2);



/**
 * \brief Calculates the minimum of two integers.
 *
 * \param[in] a The first value
 * \param[in] b The second value
 *
 * \return The lower value between \a a and \a b
 */
inline int min(const int a, const int b) {
	return a < b ? a : b;
}

/**
 * \brief Calculates the maximum of two integers.
 *
 * \param[in] a The first value
 * \param[in] b The second value
 *
 * \return The higher value between \a a and \a b
 */
inline int max(const int a, const int b) {
	return a < b ? b : a;
}


#endif /* LIBMISC_H */
