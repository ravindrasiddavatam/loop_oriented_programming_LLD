TARGETS=lop lexer_test
LOP_OBJ= add_node.o\
				        ast_node.o\
								ref_env.o\
								binop_node.o\
								lop_lexer.o\
								lop_parser.o\
								divide_node.o\
								multiply_node.o\
								number_node.o\
								array_node.o\
								hash_length_node.o\
								conditions_node.o\
								object_node.o\
								new_object_node.o\
								multi_id.o\
								function_call.o\
								function_ref.o\
								unary_node.o\
								string_node.o\
								pow_node.o\
								loop_node.o\
								subtract_node.o\
								input_node.o\
								display_node.o\
								ref_node.o\
								assign_node.o\
								if_node.o\
								stop_node.o\
								statements_node.o\

#compiler information
LD=g++
CC=g++
CXX=g++
CXXFLAGS=-g -Ilib
LDFLAGS=-Llib
LDLIBS=-lreglex

all: $(TARGETS)
lop: lop.o $(LOP_OBJ)
lexer_test: lexer_test.o lop_lexer.o

clean:
	rm -f $(TARGETS) *.o