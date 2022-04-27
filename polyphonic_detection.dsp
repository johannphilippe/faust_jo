declare name            "polyphonic_detection";
declare version         "1.0";
declare author          "Johann Philippe";
declare license         "MIT";
declare copyright       "(c) Johann Philippe 2022";

import("stdfaust.lib"); 
synt(note, atq, rel, amp) = os.sawtooth(ba.midikey2hz(note)) * amp * env  
with { 
        env = (amp > 0) : en.are(atq, rel); 
}; 
 
rms_avg = hslider("rms", 0.01, 0.0001, 0.1, 0.00001);
detect(thresh, band) = 0, brms : select2( (brms > thresh) ) 
with { 
        brms = band : an.rms_envelope_rect(rms_avg); 
}; 

N_FILTER = 4;
filter(note) = fi.bandpass(1, ba.midikey2hz(note - 0.5), ba.midikey2hz(note + 0.5));
band( note) = seq(n, N_FILTER, filter(note)); //fi.bandpass(1, ba.midikey2hz(note - 0.5), ba.midikey2hz(note + 0.5)); 
N_BANDS = 100; 
detector(thresh, atq, rel, sig) = sum(n, N_BANDS, chain(20 + n, thresh)) 
with { 
        chain(note, thresh) = synt(note, atq, rel , drms) 
        with { 
            bnd = band(note, sig) : fi.dcblocker; 
            drms = detect(thresh, bnd); 
             
        }; 
}; 

atq=  hslider("attack", 0.1, 0.05, 1, 0.01);
rel = hslider("release", 0.1, 0.01, 3, 0.01);
threshold = hslider("thresh", 0.001, 0.0001, 1, 0.0001);  
trig = button("trig");
not = hslider("note", 50, 50, 70, 1);
process = _ <: detector(threshold, atq, rel), _; 

