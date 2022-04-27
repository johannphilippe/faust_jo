declare name            "polyphonic_detection";
declare version         "1.0";
declare author          "Johann Philippe";
declare license         "MIT";
declare copyright       "(c) Johann Philippe 2022";

import("stdfaust.lib");

// Increase it for more accuracy
N_FILTER = 4;
// From midi note 20 to 125
N_BANDS = 105;

detector(thresh, rms_avg, sig) = par(n, N_BANDS, chain(20 + n))
with {
        filter(note) = fi.bandpass(1, ba.midikey2hz(note - 0.5), ba.midikey2hz(note + 0.5));
        band( note) = seq(n, N_FILTER, filter(note));

        detect(band) = 0, brms : select2( (brms > thresh) )
        with {
                brms = band : an.rms_envelope_rect(rms_avg);
        };

        chain(note) = drms
        with {
            bnd = sig : band(note) : fi.dcblocker;
            drms = detect(bnd);
        };
};


synt(note, atq, rel, amp) = os.sawtooth(ba.midikey2hz(note)) * env * amp
with {
        env = (amp > 0) : en.are(atq, rel);
};

rms_avg = hslider("rms", 0.01, 0.0001, 0.1, 0.00001);
atq =  hslider("attack", 0.1, 0.05, 1, 0.01);
rel = hslider("release", 0.1, 0.01, 3, 0.01);
threshold = hslider("thresh", 0.001, 0.0001, 1, 0.0001);
process = _ : detector(threshold, rms_avg) : par(n, N_BANDS, synt(n + 20, atq, rel)) :> _;
