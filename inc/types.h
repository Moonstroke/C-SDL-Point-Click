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



typedef const char *str; /**< A redefinition for constant srings */

/**
 * \brief A convenience macro for structure needing to be padded
 */
#define padding(s) unsigned char _padding[s]


#endif // TYPES_H
