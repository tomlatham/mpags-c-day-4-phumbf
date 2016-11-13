// Standard library includes
#include <string>
#include <vector>
#include <algorithm>
#include<iostream>
#include<map>

// Out project headers
#include "PlayfairCipher.hpp"


PlayfairCipher::PlayfairCipher( const std::string& key ) : key_("")
{
    setKey(key); 
}

void PlayfairCipher::setKey( const std::string& key )
{
    // store the original key
    key_ = key;

    // Append the alphabet
    key_ += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Make sure the key is upper case
    std::transform(key_.begin(), key_.end(), key_.begin(), toupper);
    std::cout << key_ << std::endl;

    // Remove non-alpha characters
    key_.erase(std::remove_if(key_.begin(), key_.end(), [] (unsigned char c) {return !std::isalpha(c); } ), key_.end());

    std::cout << key_ << std::endl;

    // Change J -> I
    std::transform(key_.begin(), key_.end(), key_.begin(), [] (char elem) {if (elem=='J') return 'I'; 
    else return elem;} );

    std::cout << key_ << std::endl;

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
    std::cout << key_ << std::endl;
    
    // Store the coords of each letter
   /*using l2c = std::map<char, std::pair<int, int>>;
   using c2l = std::map<std::pair<int, int>, char>;
   
   l2c l2cmymap;
   c2l c2lmymap;*/
   
   for(unsigned int i=0; i<25; i++){
   
       int ix = i%5;
       int iy = i/5;
       
       std::pair<int, int> coord(ix, iy);
       
       // Store the playfair cipher key map
       l2cmymap_[ key_[i] ] = coord;
       c2lmymap_[coord] = key_[i];
       }
     
    // Print out map contents 
    for(auto it = l2cmymap_.cbegin(); it != l2cmymap_.cend(); ++it)
    {
    std::cout << it->first << " " << it->second.first << " " << it->second.second << "\n";
    }

    
}

std::string PlayfairCipher::applyCipher(const std::string& inputText, const CipherMode /*cipherMode*/ ) const
{
    // Change J → I
     std::string playout = inputText;
     std::transform(playout.begin(), playout.end(), playout.begin(), [] (char eleme) {if (eleme=='J') return 'I'; 
     else return eleme;} );

     std::cout << playout << std::endl;
     
    // Find repeated chars and add an X
    std::string::iterator repeatiter;
    for(repeatiter = playout.begin(); repeatiter != playout.end(); repeatiter++){
        if(*(repeatiter + 1) == *(repeatiter)){
        playout.insert((repeatiter + 1),'X');
        }
    }
     
    std::cout << playout << std::endl;
    
    // if the size of input is odd, add a trailing Z
    const int n = playout.size();
    if(n % 2 != 0){
        playout += 'Z';
    }
        std::cout << playout << std::endl;

    // Loop over the input in Digraphs
    std::string::iterator digraphiter;
    for(digraphiter = playout.begin(); digraphiter != playout.end(); digraphiter+=2){

        char lett1 = *digraphiter;
        char lett2 = *(digraphiter + 1);

        //   - Find the coords in the grid for each digraph
        int lett1coord1 = l2cmymap_.find(lett1)->second.first;
        int lett1coord2 = l2cmymap_.find(lett1)->second.second;
        std::cout << lett1coord1 << lett1coord2 << std::endl;
        int lett2coord1 = l2cmymap_.find(lett2)->second.first;
        int lett2coord2 = l2cmymap_.find(lett2)->second.second;
        std::cout << lett2coord1 << lett2coord2 << std::endl;

        //   - Apply the rules to these coords to get 'new' coords
        
        
    }
    //   - Find the letter associated with the new coords
    // return the text
return playout;
}
