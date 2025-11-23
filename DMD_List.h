#ifndef DMD_LIST_H
#define DMD_LIST_H
#include <cstdint>
/*--------------------------------------------------------------------------------------*/
// container list class for DMD GPIOs and Colours
template <typename T>
class DMD_List
{
public:
	DMD_List(T pinA, T pinB) :count(2)
	{
		list = new T[2]{ pinA, pinB };
	}
	DMD_List(uint8_t pin_count, T* pinlist):count(pin_count)
	{
		list = new T[pin_count];
		memcpy(list, pinlist, count*sizeof(T));
	}

	uint8_t count = 0;
	T* list = nullptr;

	~DMD_List() { delete[] list; }

};

typedef DMD_List<uint8_t>  DMD_Pinlist;
typedef DMD_List<uint16_t>  DMD_Colorlist;

#endif