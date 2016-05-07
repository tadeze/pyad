#perceptron_supp.py

from perceptron import Perceptron

def rebuild_perceptron(wlen,freePos,fpos,w,nw_avg,wtot_avg,wsup_avg,wmean_avg,wtot_my,wac_my,wtotc_my,wmean_my):
    return Perceptron(wlen,True,freePos,fpos,w,nw_avg,wtot_avg,wsup_avg,wmean_avg,wtot_my,wac_my,wtotc_my,wmean_my)