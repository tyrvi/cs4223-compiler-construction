prgm: data algorithm;
data: DATA COLON declarationList;
declarationList: declaration END_STMT declarationList | declaration END_STMT
declaration: dataType COLON variableList;
variableList: VARIABLE COMMA variableList | VARIABLE LBRACKET INT_CONST RBRACKET COMMA variableList | VARIABLE | VARIABLE LBRACKET INT_CONST RBRACKET;
