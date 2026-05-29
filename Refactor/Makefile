# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17

#Log Separator
LOG_SEPARATOR = printf "\n========== [%s] ==========\n\n" "$$(date '+%Y-%m-%d %H:%M:%S')"

# Directories
OUTDIR = bin
LOGDIR = log
IO = i_o
DTC = data_types_and_casting
PTR = pointers
COL = collections
OOP = object_oriented_programming
F = files
THR = threads
BMK = benchmarking
DP = design_patterns
MISC = miscellaneous
STD = std_lib

# Default rule
all: clean rmlog dirs $(OUTDIR)/i_o $(OUTDIR)/data_types_and_casting \
$(OUTDIR)/pointers $(OUTDIR)/pointers_misc $(OUTDIR)/collections \
$(OUTDIR)/object_oriented_programming  $(OUTDIR)/files $(OUTDIR)/threads \
$(OUTDIR)/benchmarking $(OUTDIR)/design_patterns $(OUTDIR)/miscellaneous \
$(OUTDIR)/std_lib

# Ensure output and log directory exists
.PHONY: dirs

dirs:
	mkdir -p $(OUTDIR) $(LOGDIR)

#make bin/i_o
$(OUTDIR)/i_o : $(IO)/i_o.cpp | dirs
	@$(LOG_SEPARATOR) >> $(LOGDIR)/i_o.log 
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/i_o $(IO)/i_o.cpp 2>&1 | tee -a $(LOGDIR)/i_o.log 
	
#make bin/data_types_and_casting
$(OUTDIR)/data_types_and_casting : $(DTC)/data_types.cpp $(DTC)/type_casting.cpp $(DTC)/decltype.cpp| dirs
	@$(LOG_SEPARATOR) >> $(LOGDIR)/data_types.log 
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/data_types $(DTC)/data_types.cpp 2>&1 | tee -a $(LOGDIR)/data_types_and_casting.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/type_casting $(DTC)/type_casting.cpp 2>&1 | tee -a $(LOGDIR)/data_types_and_casting.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/decltype $(DTC)/decltype.cpp 2>&1 | tee -a $(LOGDIR)/data_types_and_casting.log  
	
#make bin/pointers
$(OUTDIR)/pointers : $(PTR)/pointers.c $(PTR)/pointers_misc.c $(PTR)/pointers_to_function.cpp | dirs
	@$(LOG_SEPARATOR) >> $(LOGDIR)/pointers.log 
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/pointers $(PTR)/pointers.c 2>&1 | tee -a $(LOGDIR)/pointers.log 
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/pointers_misc $(PTR)/pointers_misc.c 2>&1 | tee -a $(LOGDIR)/pointers.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/pointers_to_function $(PTR)/pointers_to_function.cpp 2>&1 | tee -a $(LOGDIR)/pointers.log 



#make bin/collections	
$(OUTDIR)/collections : $(COL)/collections.cpp | dirs
	@$(LOG_SEPARATOR) >> $(LOGDIR)/collections.log 
	$(CXX) $(CXXFLAGS) -Iinclude \
	$(COL)/collections.cpp \
	$(COL)/array.cpp \
	$(COL)/enum.cpp \
	$(COL)/list.cpp \
	$(COL)/map.cpp \
	$(COL)/queue.cpp \
	$(COL)/vector.cpp \
	-o $(OUTDIR)/collections 2>&1 | tee -a $(LOGDIR)/collections.log 

#make bin/object_oriented_programming
$(OUTDIR)/object_oriented_programming : $(OOP)/object_oriented_programming.cpp | dirs
	@$(LOG_SEPARATOR) >> $(LOGDIR)/object_oriented_programming.log 
	$(CXX) $(CXXFLAGS) -Iinclude \
	$(OOP)/object_oriented_programming.cpp \
    	$(OOP)/entity.cpp \
    	$(OOP)/player.cpp \
    	$(OOP)/enemy.cpp \
    	$(OOP)/opponent.cpp \
	-o $(OUTDIR)/object_oriented_programming 2>&1 | tee -a $(LOGDIR)/object_oriented_programming.log 

#make bin/files
$(OUTDIR)/files : $(F)/files.cpp | dirs
	@$(LOG_SEPARATOR) >> $(LOGDIR)/files.log 
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/files $(F)/files.cpp 2>&1 | tee -a $(LOGDIR)/files.log 

#make bin/threads
$(OUTDIR)/threads : $(THR)/threads.cpp $(THR)/mutex.cpp $(THR)/arguments.cpp $(THR)/condition_variable.cpp $(THR)/future_async.cpp $(THR)/packaged_task.cpp $(THR)/promise.cpp $(THR)/thread_guard.cpp $(THR)/thread_spawn.cpp | dirs
	@$(LOG_SEPARATOR) >> $(LOGDIR)/threads.log 
	$(CXX) $(CXXFLAGS) -pthread -o $(OUTDIR)/threads $(THR)/threads.cpp 2>&1 | tee -a $(LOGDIR)/threads.log
	$(CXX) $(CXXFLAGS) -pthread -o $(OUTDIR)/mutex $(THR)/mutex.cpp 2>&1 | tee -a $(LOGDIR)/threads.log
	$(CXX) $(CXXFLAGS) -pthread -o $(OUTDIR)/arguments $(THR)/arguments.cpp 2>&1 | tee -a $(LOGDIR)/threads.log
	$(CXX) $(CXXFLAGS) -pthread -o $(OUTDIR)/condition_variable $(THR)/condition_variable.cpp 2>&1 | tee -a $(LOGDIR)/threads.log
	$(CXX) $(CXXFLAGS) -pthread -o $(OUTDIR)/future_async $(THR)/future_async.cpp 2>&1 | tee -a $(LOGDIR)/threads.log
	$(CXX) $(CXXFLAGS) -pthread -o $(OUTDIR)/packaged_task $(THR)/packaged_task.cpp 2>&1 | tee -a $(LOGDIR)/threads.log
	$(CXX) $(CXXFLAGS) -pthread -o $(OUTDIR)/promise $(THR)/promise.cpp 2>&1 | tee -a $(LOGDIR)/threads.log
	$(CXX) $(CXXFLAGS) -pthread -o $(OUTDIR)/thread_guard $(THR)/thread_guard.cpp 2>&1 | tee -a $(LOGDIR)/threads.log
	$(CXX) $(CXXFLAGS) -pthread -o $(OUTDIR)/thread_spawn $(THR)/thread_spawn.cpp 2>&1 | tee -a $(LOGDIR)/threads.log

#make bin/benchmarking
$(OUTDIR)/benchmarking : $(BMK)/benchmarking.cpp | dirs
	@$(LOG_SEPARATOR) >> $(LOGDIR)/benchmarking.log 
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/benchmarking $(BMK)/benchmarking.cpp 2>&1 | tee -a $(LOGDIR)/benchmarking.log

#make bin/design_patterns
$(OUTDIR)/design_patterns : \
$(DP)/neural_network.cpp $(DP)/singleton.cpp $(DP)/monostate.cpp \
$(DP)/factory.cpp $(DP)/inner_factory.cpp $(DP)/prototype_factory.cpp $(DP)/groovy_builder.cpp $(DP)/fluent_builder.cpp \
$(DP)/static_decorator.cpp $(DP)/dynamic_decorator.cpp $(DP)/functional_decorator.cpp \
$(DP)/object_duplication.cpp $(DP)/property_proxy.cpp $(DP)/virtual_proxy.cpp \
$(DP)/memento.cpp $(DP)/flyweight.cpp $(DP)/mediator.cpp $(DP)/pointer_chain.cpp  \
$(DP)/filter.cpp | dirs
	@$(LOG_SEPARATOR) >> $(LOGDIR)/design_patterns.log 
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/neural_network $(DP)/neural_network.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log  
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/singleton $(DP)/singleton.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/monostate $(DP)/monostate.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/factory $(DP)/factory.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/inner_factory $(DP)/inner_factory.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/prototype_factory $(DP)/prototype_factory.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/groovy_builder $(DP)/groovy_builder.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/fluent_builder $(DP)/fluent_builder.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/static_decorator $(DP)/static_decorator.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/dynamic_decorator $(DP)/dynamic_decorator.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/functional_decorator $(DP)/functional_decorator.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/object_duplication $(DP)/object_duplication.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/property_proxy $(DP)/property_proxy.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/virtual_proxy $(DP)/virtual_proxy.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/memento $(DP)/memento.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/flyweight $(DP)/flyweight.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/mediator $(DP)/mediator.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/pointer_chain $(DP)/pointer_chain.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/filter $(DP)/filter.cpp 2>&1 | tee -a $(LOGDIR)/design_patterns.log

#make bin/miscellaneous
$(OUTDIR)/miscellaneous : \
$(MISC)/const.cpp $(MISC)/enumeration.cpp $(MISC)/functor.cpp $(MISC)/iterators.cpp $(MISC)/operator_overloading.cpp \
$(MISC)/declspec_assume_restrict.cpp $(MISC)/template.cpp $(MISC)/inline_function.cpp $(MISC)/lambda_expression.cpp \
$(MISC)/exceptions.cpp $(MISC)/bit_mask.cpp $(MISC)/lvalue_rvalue.cpp $(MISC)/adl_arument_dependant_lookup.cpp \
$(MISC)/attributes.cpp $(MISC)/boolalpha.cpp $(MISC)/macros.cpp $(MISC)/memery_allignment.cpp \
$(MISC)/memory_allocation_tracking.cpp $(MISC)/move_semantics.cpp $(MISC)/mutable.cpp $(MISC)/namespace.cpp \
$(MISC)/small_string_optimization.cpp $(MISC)/static_assert.cpp $(MISC)/variadic_functions.cpp $(MISC)/volatile.cpp \
$(MISC)/trailing_return_type.cpp $(MISC)/callback_with_type_definition.cpp | dirs
	@$(LOG_SEPARATOR) >> $(LOGDIR)/miscellaneous.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/const $(MISC)/const.cpp 2>&1 | tee -a $(LOGDIR)/miscellaneous.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/enumeration $(MISC)/enumeration.cpp 2>&1 | tee -a $(LOGDIR)/miscellaneous.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/functor $(MISC)/functor.cpp 2>&1 | tee -a $(LOGDIR)/miscellaneous.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/iterators $(MISC)/iterators.cpp 2>&1 | tee -a $(LOGDIR)/miscellaneous.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/operator_overloading $(MISC)/operator_overloading.cpp 2>&1 | tee -a $(LOGDIR)/miscellaneous.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/declspec_assume_restrict $(MISC)/declspec_assume_restrict.cpp 2>&1 | tee -a $(LOGDIR)/miscellaneous.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/template $(MISC)/template.cpp 2>&1 | tee -a $(LOGDIR)/miscellaneous.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/inline_function $(MISC)/inline_function.cpp 2>&1 | tee -a $(LOGDIR)/miscellaneous.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/lambda_expression $(MISC)/lambda_expression.cpp 2>&1 | tee -a $(LOGDIR)/miscellaneous.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/exceptions $(MISC)/exceptions.cpp 2>&1 | tee -a $(LOGDIR)/miscellaneous.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/bit_mask $(MISC)/bit_mask.cpp 2>&1 | tee -a $(LOGDIR)/miscellaneous.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/lvalue_rvalue $(MISC)/lvalue_rvalue.cpp 2>&1 | tee -a $(LOGDIR)/miscellaneous.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/adl_arument_dependant_lookup $(MISC)/adl_arument_dependant_lookup.cpp 2>&1 | tee -a $(LOGDIR)/miscellaneous.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/attributes $(MISC)/attributes.cpp 2>&1 | tee -a $(LOGDIR)/miscellaneous.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/boolalpha $(MISC)/boolalpha.cpp 2>&1 | tee -a $(LOGDIR)/miscellaneous.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/macros $(MISC)/macros.cpp 2>&1 | tee -a $(LOGDIR)/miscellaneous.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/memery_allignment $(MISC)/memery_allignment.cpp 2>&1 | tee -a $(LOGDIR)/miscellaneous.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/memory_allocation_tracking $(MISC)/memory_allocation_tracking.cpp 2>&1 | tee -a $(LOGDIR)/miscellaneous.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/move_semantics $(MISC)/move_semantics.cpp 2>&1 | tee -a $(LOGDIR)/miscellaneous.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/mutable $(MISC)/mutable.cpp 2>&1 | tee -a $(LOGDIR)/miscellaneous.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/namespace $(MISC)/namespace.cpp 2>&1 | tee -a $(LOGDIR)/miscellaneous.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/small_string_optimization $(MISC)/small_string_optimization.cpp 2>&1 | tee -a $(LOGDIR)/miscellaneous.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/static_assert $(MISC)/static_assert.cpp 2>&1 | tee -a $(LOGDIR)/miscellaneous.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/variadic_functions $(MISC)/variadic_functions.cpp 2>&1 | tee -a $(LOGDIR)/miscellaneous.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/volatile $(MISC)/volatile.cpp 2>&1 | tee -a $(LOGDIR)/miscellaneous.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/trailing_return_type $(MISC)/trailing_return_type.cpp 2>&1 | tee -a $(LOGDIR)/miscellaneous.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/callback_with_type_definition $(MISC)/callback_with_type_definition.cpp 2>&1 | tee -a $(LOGDIR)/miscellaneous.log

#make bin/std_lib
$(OUTDIR)/std_lib : \
$(STD)/algorithm.cpp $(STD)/chrono.cpp $(STD)/functional.cpp | dirs
	@$(LOG_SEPARATOR) >> $(LOGDIR)/std_lib.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/algorithm $(STD)/algorithm.cpp 2>&1 | tee -a $(LOGDIR)/std_lib.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/chrono $(STD)/chrono.cpp 2>&1 | tee -a $(LOGDIR)/std_lib.log
	$(CXX) $(CXXFLAGS) -o $(OUTDIR)/functional $(STD)/functional.cpp 2>&1 | tee -a $(LOGDIR)/std_lib.log

# Clean build files
clean:
	rm -rf $(OUTDIR) 

# Remove log files
rmlog: 
	rm -rf $(LOGDIR)
