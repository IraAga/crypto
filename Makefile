
clean:
	rm -rf *.out
	rm -rf demo_otp
	rm -rf demo_cc
	rm -rf demo_sc
	rm -rf demo_vc
	
demo_otp: demo_otp.c crypto.c crypto.h 
	gcc $^ -o $@

demo_cc: demo_cc.c crypto.c crypto.h 
	gcc $^ -o $@ 

demo_sc: demo_sc.c crypto.c crypto.h 
	gcc $^ -o $@

demo_vc: demo_vc.c crypto.c crypto.h 
	gcc $^ -o $@

all: demo_otp demo_cc demo_sc demo_vc 
