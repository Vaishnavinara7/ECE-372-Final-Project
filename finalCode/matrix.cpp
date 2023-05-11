#include <avr/interrupt.h>
#include <avr/io.h>
#include "matrix.h"
#include "Arduino.h"

void MatrixInit() {
    // Order of Ports : H6, H5, H4, H3, E3, G5, E5, E4 (9 to 2)
    
    DDRH |= ((1 << DDH6)| (1 << DDH5) | (1 << DDH4) | (1 << DDH3)); // set to outputs
    DDRE &= ~((1 << DDE3) | (1 << DDE4) | (1<<DDE5)); // set to inputs
    DDRG &= ~((1 << DDG5));


    PORTH |= ((1 << PORTH6)| (1 << PORTH5) | (1 << PORTH4) | (1 << PORTH3));
    PORTE |= ((1 << PORTE3) | (1 << PORTE4) | (1<<PORTE5));
    PORTG |= ((1 << PING5));

    
}

int ReadValue(){
    PORTH &= ~(1 << PORTH6);
    PORTH |= (1 << PORTH5);
    PORTH |= (1 << PORTH4);
    PORTH |= (1 << PORTH3);
        if (!(PINE & (1 << PINE4))){
        
            return -1;
        }
        else if (!(PINE & (1 << PINE5))){
           
            return 3;
        }
        else if (!(PING & (1 << PING5))){
            
            return 2;
        }
        else if (!(PINE & (1 << PINE3))){
          
            return 1;
        }                       
        else{
            
            PORTH |= (1 << PORTH6);
            PORTH &= ~(1 << PORTH5);
            PORTH |= (1 << PORTH4);
            PORTH |= (1 << PORTH3);
                if (!(PINE & (1 << PINE4))){
                    return -1;
                }
                else if (!(PINE & (1 << PINE5))){
                    return 6;
                }
                else if (!(PING & (1 << PING5))){
                    return 5;
                }
                else if (!(PINE & (1 << PINE3))){
                    return 4;
                }  
                else{                     
        
                    PORTH |= (1 << PORTH6);
                    PORTH |= (1 << PORTH5);
                    PORTH &= ~(1 << PORTH4);
                    PORTH |= (1 << PORTH3);
                        if (!(PINE & (1 << PINE4))){
                            return -1;
                        }
                        else if (!(PINE & (1 << PINE5))){
                            return 9;
                        }
                        else if (!(PING & (1 << PING5))){
                            return 8;
                        }
                        else if (!(PINE & (1 << PINE3))){
                            return 7;
                        }   
                        else{                 
                    
                                PORTH |= (1 << PORTH6);
                                PORTH |= (1 << PORTH5);
                                PORTH |= (1 << PORTH4);
                                PORTH &= ~(1 << PORTH3);
                                    if (!(PINE & (1 << PINE4))){
                                        return -1;
                                    }
                                    else if (!(PINE & (1 << PINE5))){
                                        return -1;
                                    }
                                   else if (!(PING & (1 << PING5))){
                                        return 0;
                                    }
                                    else if (!(PINE & (1 << PINE3))){
                                        return -1;
                                    }    
                                    else{
                                        return -1;
                                    }  
                        }
                }
        }
                
            

   

}