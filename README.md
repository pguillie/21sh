#21sh

/!\ SANS TERMCAPS /!\

##PB:
	leaks sh_token_new
	setenv HOME passe mal
	ls nofile 2>&- : ne ferme pas
	jump cvx
	si PATH='/' probleme avec is_directory();
	redirection au dela de 2 (EX: ls 1>&3)

##BONUS:

	recherche historique (^R)
	table de hash
	completion

##5-bonus:

	prompt
	copier-colle sys
	tilde
	coloration syntaxique
	~ hash
	~ recherche historique (^S)
	snake ??
	printenv
	esc+touche
	View  

