# use /usr/local/cuda/extras/demo_suite/deviceQuery to decide SMS 
SMS:= 50 86 
CC         := nvcc 
LINKER     := $(CC)
CFLAGS     := -std=c++17 -O2 -g
LDFLAGS    := -lm  -lcublas  -lopenblas  
$(foreach sm,$(SMS),$(eval GENCODE_FLAGS += -gencode arch=compute_$(sm),code=sm_$(sm)))

# the test case define 
target := cuda/gemm_v1.cu 
test_src = $(wildcard $(target)) 
test_obj = $(patsubst %.cu,%.o,$(test_src))

# the utils 
utils_h := common
# utils := common/*.cpp 
# utils_src = $(wildcard $(utils)) 
# utils_obj = $(patsubst  %.h,%.o,$(utils_src))

#.cpp and .cu how to convert to .o
%.o: %.cpp 
	$(CC) $(CFLAGS) $(GENCODE_FLAGS)   -c $< -o $@
%.o: %.cu
	$(CC) $(CFLAGS) $(GENCODE_FLAGS)  -c $< -o $@

# main.o:main.cpp 
# 	$(CC) $(CFLAGS) $(GENCODE_FLAGS) -I$(utils_h)  -c $< -o $@  

all: 
	make clean;
	make main 

main: main.o ${test_obj}   
	$(LINKER)   $(LDFLAGS)  main.o ${test_obj}  -o $@


clean:
	rm -f *.o *~ core *.x  $(test_obj) $(utils_obj)
