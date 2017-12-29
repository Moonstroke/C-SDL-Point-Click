/**
 * \file types.h
 * \author joH1
 *
 * \version 0.1
 *
 * \brief Some usefule types definitions.
 *
 * This file contains several definitions of types used throughout the whole
 * project.
*/

#ifndef TYPES_H
#define TYPES_H



/**
 * \brief A redefinition for constant strings
*/
typedef const char *str;

/**
 * \brief A convenience macro for structure needing to be padded
 */
#define padding(size) unsigned char _padding[size]


#endif // TYPES_H
