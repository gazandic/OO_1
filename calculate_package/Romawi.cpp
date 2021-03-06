#include "Romawi.h"
#include "RomawiExp.h"

std::string BilanganRomawi::toString(int bil) {
	struct bilromawi_t { int value; char const* numeral; };
	
	bilromawi_t const bilromawi[] = 
     { 1000, "M",
        900, "CM",
        500, "D",
        400, "CD",
        100, "C",
         90, "XC",
         50, "L",
         40, "XL",
         10, "X",
          9, "IX",
          5, "V",
          4, "IV",
          1, "I",
          0, NULL };
     std::string result;

     for(bilromawi_t const* current = bilromawi; current->value > 0; ++current) {
     	while (bil >= current->value) {
     		result += current->numeral;
     		bil -= current->value;
     	}
     }

     return result;
}


int BilanganRomawi::hitung(std::string OP1, std::string OP2, std::string OP) {
  if (OP == "+") return tambah(OP1, OP2);
  else if (OP == "-") return kurang(OP1, OP2);
  else if (OP == "*") return kali(OP1, OP2);
  else if (OP == "/") return bagi(OP1, OP2);
  else return 0;
}

int BilanganRomawi::toInt(std::string bil) {

	int result = 0;

	for (int i = 0; i < bil.size(); i++) {
		if (i > 0 && intRomawi(bil[i]) > intRomawi(bil[i - 1])) {
			result += intRomawi(bil[i]) - 2 * intRomawi(bil[i - 1]);
		} else {
			result += intRomawi(bil[i]);
		}
	}

	return result;
}
int BilanganRomawi::tambah(std::string OP1, std::string OP2) {  
  return toInt(OP1) + toInt(OP2);
}

int BilanganRomawi::kurang(std::string OP1, std::string OP2) {
  int result = toInt(OP1) - toInt(OP2);
  if (result == 0) 
    throw(RomawiExp(VALUE_ZERO));
  else if (result < 0) 
    throw(RomawiExp(NEGATIVE_VALUE));
  return result;
}

int BilanganRomawi::kali(std::string OP1, std::string OP2) {
  int result = toInt(OP1) * toInt(OP2);
  if (result > 4000)
    throw(RomawiExp(LARGE_NUMBER));
  return result;
}

int BilanganRomawi::bagi(std::string OP1, std::string OP2) {
  if (toInt(OP2) == 0)
    throw(RomawiExp(DIVIDE_BY_ZERO));
  return toInt(OP1) / toInt(OP2);
}

int BilanganRomawi::intRomawi(char c) {  
  switch(c) {  
    case 'I': return 1;  
    case 'V': return 5;  
    case 'X': return 10;  
    case 'L': return 50;  
    case 'C': return 100;  
    case 'D': return 500;  
    case 'M': return 1000;  
     default: return 0;  
   }  
}