#perceptron.pyx

import numpy as np
cimport numpy as np
cimport cython

#added
from perceptron_supp import rebuild_perceptron

cdef class Perceptron:
    cdef int wlen,freePos
    cdef dict fpos

    cdef np.ndarray w #np.ndarray[np.int32_t]

    cdef int nw_avg
    cdef np.ndarray wtot_avg,wsup_avg #np.ndarray[np.int32_t]
    cdef np.ndarray wmean_avg  #np.ndarray[np.float64_t]

    cdef np.ndarray wtot_my,wac_my,wtotc_my #np.ndarray[np.int32_t]
    cdef np.ndarray wmean_my  #np.ndarray[np.float64_t]

    def __cinit__(self,int wlen=4*10**7,setValues=False,freePos=0,fpos=0,w=0,nw_avg=0,wtot_avg=0,wsup_avg=0,wmean_avg=0,wtot_my=0,wac_my=0,wtotc_my=0,wmean_my=0):
        if not setValues:            
            self.wlen=wlen
            self.freePos=1
            self.fpos= dict()

            self.w=np.zeros(wlen,np.int32)

            self.nw_avg=1
            self.wtot_avg=np.zeros(wlen,np.int32)            
            self.wsup_avg=np.zeros(wlen,np.int32)
            self.wmean_avg=np.zeros(wlen,np.float64)

            self.wtot_my=np.zeros(wlen,np.int32)    
            self.wac_my=np.zeros(wlen,np.int32)
            self.wtotc_my=np.zeros(wlen,np.int32)
            self.wmean_my=np.zeros(wlen,np.float64)
        else:           
            self.wlen=wlen
            self.freePos=freePos
            self.fpos=fpos

            self.w=w

            self.nw_avg=nw_avg
            self.wtot_avg=wtot_avg
            self.wsup_avg=wsup_avg
            self.wmean_avg=wmean_avg

            self.wtot_my=wtot_my
            self.wac_my=wac_my
            self.wtotc_my=wtotc_my
            self.wmean_my=wmean_my

    def __reduce__(self):
        return (rebuild_perceptron,(self.wlen,self.freePos,self.fpos,self.w,self.nw_avg,self.wtot_avg,self.wsup_avg,self.wmean_avg,self.wtot_my,self.wac_my,self.wtotc_my,self.wmean_my))
