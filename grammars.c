


mpc_parser_t* Adjective = mpc_or(4,
  mpc_sym("wow"), mpc_sym("many"),
  mpc_sym("so"), mpc_sym("such")
);

mpc_parser_t* Noun = mpc_or(5,
  mpc_sym("lisp"), mpc_sym("language"),
  mpc_syn("book"), mpc_sym("build"),
  mpc_sym("c")
);

mpc_parser_t* Phrase = mpc_and(2, mpcf_strfold,
  Adjective, Noun, free);

mpc_parser_t* Doge = mpc_many(mpcf_strfold, Phrase);


------
------
------
------
------
------
------

mpc_parser_t* Adjective = mpc_new("adjective");
mpc_parser_t* Noun = mpc_new("noun");
mpc_parser_t* Phrase = mpc_new("phrase");
mpc_parser_t* Doge = mpc_new("doge");

