# Malloc

The objective of this project is to reimplement the malloc, realloc and free functions.

## Malloc

The malloc (in this project) must separate tiny, small and large allocations. 

For some optimization purpose, the newest allocations are located near the beginning of the double linked list.

<p align="center">
<img src="imgs/malloc_zones.png" alt="drawing" width="800"/>
<p/>

For tiny and small zones this structure has been followed.

<p align="center">
<img src="imgs/malloc_struct.png" alt="drawing" width="800"/>
<p/>

whereas for large zones, the bloc is allocated directly in the zone.

<p align="center">
<img src="imgs/malloc_large.png" alt="drawing" width="800"/>
<p/>

## Free

The free implementation flags the freed blocs for new allocations. If the entire zone is freed then free munmap the zone (real free). Free also performs a defragmentation to "concatenate" freed blocs located next to eachother.

## Realloc

Realloc will change the size if an allocation. First, it will try to allocate more space at the end of the already allocated bloc. If it cannot, realloc will free the bloc and run another malloc of the new size.

### Mark (118/125)