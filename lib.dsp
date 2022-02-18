declare name            "faust_jo";
declare version         "1.0";
declare author          "Johann Philippe";
declare license         "MIT";
declare copyright       "(c) Johann Philippe 2022";

import("stdfaust.lib");


jo = environment {
	/*
		Impulsion with a specified duration. Can be retriggered.
	*/
	mpulse(smps_dur, trig) = pulsation
	with {
	    count = ba.countdown(smps_dur, trig);
	    //count =  -(1)~_, smps_dur : select2(trig);
	    pulsation = 0, 1 : select2(count > 0);
	};
	mpulse_dur(duration, trig) = mpulse(ba.sec2samp(duration), trig);

	/*
		Euclidian function. Generates an euclidian rythm with 0;1 triggers
	*/
	euclidian(onset, div, pulses, rotation, phasor) = res
	with {
	    kph = int( ((phasor * div) % 1) * pulses);
	    eucval = int((onset / pulses) * kph);
	    cond(index) = 0, 1 : select2(eucval' != eucval);
	    trig = 0, 1 : select2(kph' != kph);
	    res = (trig & cond(kph));
	};

	dur_smps_euclidian(onset, div, pulses, rotation, smps_dur, phasor) = euclidian(onset, div, pulses, rotation, phasor) : mpulse(smps_dur);


	/*
		Wavefolder. 
	*/
	wavefold(sig) = do_transform(sig), sig : select2((sig > -1) & (sig < 1))
	with {
	    abs_sig = abs(sig);
	    decimal = abs_sig - int(abs_sig);
	    neg_plus_decimal = -1 + decimal;
	    pos_minus_decimal = 1 - decimal;
	    process_value(x) = 1 - decimal, -1 + decimal : select2(x);
	    is_even = ((int(abs_sig) %2) == 0);
	    is_positiv = sig >= 0;
	    do_transform(sig) = process_value( (is_even & is_positiv) | ( (is_even == 0) & (is_positiv == 0)) );
	};
	
	/*
		Waveshaper with wavefolder.
	*/
	nonlinear_wavefold(amount, sig) = final
	with {
		transfer_fct = waveform{-1, -1, 1, 1};
		fold = wavefold(sig);
		fold_sig = (fold + 1) / 2;
		nonlinear = transfer_fct, int(fold_sig * 4) : rdtable;
		final = (nonlinear * amount) + ((1 - amount) * fold);

	};

	/*
		Limit to range
	*/
	range(vmin, vmax, sig) = res 
	with {
		low = vmin, sig : select2(sig >= vmin) ;
		res = vmax, low : select2(low <= vmax);
	};    
	
	/*
		Returns 0 if below th.
	*/
	threshold(th, sig) = sig, 0 : select2(sig <= th);

	capture_mov(th, release_time, sig) = res
	letrec {
		'inc = (abs(sig' - sig)) : threshold(th);
		'is_moving = (abs(sig' - sig)) : threshold(th) > 0;
		'dec =  (res / (release_time * ma.SR)) : *(-1) : ba.sAndH(is_moving);
		'mv = dec, inc : select2(is_moving);
		'res = _~+(mv) : range(0, 1);
	};

};