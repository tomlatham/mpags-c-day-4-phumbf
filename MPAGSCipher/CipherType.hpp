#ifndef MPAGSCIPHER_CIPHERTYPE_HPP
#define MPAGSCIPHER_CIPHERTYPE_HPP

/**
 * \file CipherType.hpp
 * \brief Contains the declaration of the CipherType enumeration
 */

/**
 * \enum CipherType
 * \brief Enumeration to define the modes in which the ciphers can operate
 */

enum class CipherType {
    Caesar, ///< Apply the Caesar Cipher 
    Playfair ///< Apply the Playfair cipher
};

#endif // MPAGSCIPHER_CIPHERTYPE_HPP 
