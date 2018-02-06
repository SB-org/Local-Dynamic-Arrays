#if defined _dyn_arrays_included
    #endinput
#endif
#define _dyn_arrays_included

#if !defined MAX_DYNAMIC_MEMORY
    #define MAX_DYNAMIC_MEMORY	4096
#endif

new tag:dyn_arr@mem[1][MAX_DYNAMIC_MEMORY];

#define new[%0]		dyn_arr@alloc(%0)
#define delete[%0]	dyn_arr@delete(%0)
#define ref<%0>		dyn_arr@ref(%0)

#define _$%0[           (dyn_arr@pointer(%0), dyn_arr@mem[0][0])[

stock tag:dyn_arr@alloc(size)
{
    assert(size < MAX_DYNAMIC_MEMORY);

    new pointer;

    emit 
    {
	load.s.pri (size >> 2) 	    // Load "size" value into PRI and multiply it by 4 to get number of bytes
	move.alt 		    // Move the value to alt
	lctrl 2			    // Load HEA into PRI
	stor.s.pri pointer 	    // Load HEA into "pointer"
	add			    // Add HEA(pri) and size(alt) together
	sctrl 2			    // Allocate memory by moving the heap pointer
    }
    return pointer;
}

stock dyn_arr@pointer(tag:pointer) 
{
    emit 
    {
	const.alt dyn_arr@mem	    // Get "dyn_arr@mem"'s header address
	load.s.pri pointer 	    // Load "pointer" value into PRI
	sub			    // PRI -= ALT / get the distance
	stor.i 			    // Store the distance in the header
    }
}

stock tag:dyn_arr@delete(pointer)
{
    new heap_size;
	
    emit lctrl 2 		    // Load HEA into PRI
    emit stor.s.pri heap_size	    // Store HEA into "heap_size"
	
    if(pointer < heap_size)	    // Only free memory if it's below the heap pointer
    {
        emit lref.s.pri pointer     // Load "pointer" value into PRI
	emit sctrl 2 		    // Put HEA to where it belongs
    }
    pointer = 0;
}

stock tag:dyn_arr@ref()
{
    emit load.s.pri 12	            // Load first param's address
    emit retn
}

stock dyn_arr@clear()
{
    dyn_arr@mem[0][0] = 0;          // Clearing the array
}
