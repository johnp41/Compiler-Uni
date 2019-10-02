
%token  id
%token integer_const

%left     '+'
%left     '^'
%left     '@'

%% 
expr : l_value | r_value ;
l_value : l_value_simple | l_value '^' | r_value_simple '^';
l_value_simple : id
r_value : r_value_simple | expr '+' expr  ;
r_value_simple : integer_const | '@' l_value_simple ;

%%
