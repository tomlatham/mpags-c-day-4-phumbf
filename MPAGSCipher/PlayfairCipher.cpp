// Standard library includes
#include <string>
#include <vector>
#include <algorithm>
#include<iostream>
#include<map>

// Out project headers
#include "PlayfairCipher.hpp"

//Constructor
PlayfairCipher::PlayfairCipher( const std::string& key ) : key_("")
{
    setKey(key); 
}

//Setting up the key
void PlayfairCipher::setKey( const std::string& key )
{
    // store the original key
    key_ = key;

    // Append the alphabet
    key_ += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Make sure the key is upper case
    std::transform(key_.begin(), key_.end(), key_.begin(), toupper);

    // Remove non-alpha characters
    key_.erase(std::remove_if(key_.begin(), key_.end(), [] (unsigned char c) {return !std::isalpha(c); } ), key_.end());

    // Change J -> I
    std::transform(key_.begin(), key_.end(), key_.begin(), [] (char elem) {if (elem=='J') return 'I'; 
    else return elem;} );

    // Remove duplicated letters
    std::string lettersseen{""}; 
    auto func = [&lettersseen] (char b) {
        if (lettersseen.find(b) != std::string::npos){
            return true;
        }
        else{
            lettersseen += b;
            return false;
        }
        
    };
            
    key_.erase(std::remove_if(key_.begin(), key_.end(), func), key_.end());
    
    // Store the coords of each letter
   for(unsigned int i=0; i<25; i++){
   
       //Calculate the coords
       int ix = i%5;
       int iy = i/5;
       
       //Define pair using the coords
       std::pair<int, int> coord(ix, iy);
       
       // Store the playfair cipher key map
       l2cmymap_[ key_[i] ] = coord;
       c2lmymap_[coord] = key_[i];
       }
}

//The Playfair cipher program
std::string PlayfairCipher::applyCipher(const std::string& inputText, const CipherMode cipherMode ) const
{
    // Setup the output
    std::string playfairout{""};
    
    // Change J → I
     std::string playout = inputText;
     std::transform(playout.begin(), playout.end(), playout.begin(), [] (char eleme) {if (eleme=='J') return 'I'; 
     else return eleme;} );
     
    // Find repeated chars in a single Digraph and add an X, or Q if the X is repeated
    size_t number = playout.length();
    for(size_t i{0}; i < number; i+=2){
        
        if(playout[i] == playout[i+1] && playout[i] != 'X'){
            
            playout.insert(i +1,"X");
            number = playout.length();
        }
        
        
        else if(playout[i] == playout[i+1] && playout[i] == 'X'){
            playout.insert(i +1,"Q");
            number = playout.length();
        
        }
    }
         
    // if the size of input is odd, add a trailing Z
    if ( number % 2 !=0){
        if(*playout.end() == 'Z') playout +="Q";
        else playout += "Z";
    }

    // Loop over the input in Digraphs, use a shift to differentiate between encrypting and decrypting
    std::string::iterator digraphiter;
    int shift = (cipherMode == CipherMode::Encrypt) ? 1 : -1;
    for(digraphiter = playout.begin(); digraphiter != playout.end(); digraphiter+=2){

        // Store the letters of the digraph
        char lett1 = *digraphiter;
        char lett2 = *(digraphiter + 1);

        //   - Find the coords in the grid for each digraph
        int lett1coord1 = l2cmymap_.find(lett1)->second.first;
        int lett1coord2 = l2cmymap_.find(lett1)->second.second;
        int lett2coord1 = l2cmymap_.find(lett2)->second.first;
        int lett2coord2 = l2cmymap_.find(lett2)->second.second;

        //   - Apply the rules to these coords to get 'new' coords
        // Declare new coords
        int newlett1coord1;
        int newlett1coord2;
        int newlett2coord1;
        int newlett2coord2;
        
        // - Check if on same row
        if(lett1coord2 == lett2coord2){
            newlett1coord1 = ((lett1coord1 + shift) > -1) ? (( lett1coord1 + shift) % 5) : 4;
            newlett2coord1 = ((lett2coord1 + shift) > -1) ? (( lett2coord1 + shift) % 5) : 4;
            newlett1coord2 = lett1coord2;
            newlett2coord2 = lett2coord2;
            
        }
        
        // - Check if in same column
        else if(lett1coord1 == lett2coord1){
            newlett1coord2 = ((lett1coord2 + shift) > -1) ? (( lett1coord2 + shift) % 5) : 4;
            newlett2coord2 = ((lett2coord2 + shift) > -1) ? (( lett2coord2 + shift) % 5) : 4;
            newlett1coord1 = lett1coord1;
            newlett2coord1 = lett2coord1;
        }
        
        // - Switch corners
        else{
            newlett1coord1 = lett2coord1;
            newlett2coord1 = lett1coord1;
            newlett1coord2 = lett1coord2;
            newlett2coord2 = lett2coord2;
            
        }
        
        //   - Find the letter associated with the new coords
        std::pair<int, int> npair1(newlett1coord1,newlett1coord2);
        std::pair<int, int> npair2(newlett2coord1,newlett2coord2);

        char nlett1 = c2lmymap_.find(npair1)->second;
        char nlett2 = c2lmymap_.find(npair2)->second;
        
        // Add to output string
        playfairout += nlett1;
        playfairout += nlett2;

            
    }
   
    // return the text
return playfairout;
}
