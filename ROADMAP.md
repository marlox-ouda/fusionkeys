# Version alpha1

Implement basic translation with hardcoded key in actions
	fk_translate(char *) -> char *
	"qwe"             -> A_UP, A_LEFT, A_PLAY

# Version alpha2

Use config file instead of hardcoded translation
        DEFAULT = SILENT
	'q' = A_UP
	'w' = A_LEFT
	fk_translate(char *) -> char *
	"qw"             -> A_UP, A_LEFT

# Version alpha3

Implement translation interruption
	fk_pause()
	fk_translate(char *) -> char *
	"qwerty"             -> "qwerty"
	fk_resume()

# Version alpha4

Implement sequence of keys in translation table
	'q+w' = A_UP
	fk_translate(char *) -> char *
	"qw"                 -> A_UP

# Version alpha5

Implement modal state for the keys
	DEFAULT_MODE = ''
	[mode a]
	'q' = jump:b
	[mode b]
	'w' = A_UP
	'e' = A_LEFT
	fk_translate(char *) -> char *
	"weqwe"              -> A_UP, A_LEFT

# Version alpha6

Implement mixed state (text and action)
	Only modal can give action

# Version alpha7

Implement stacked modal state
	[mode a]
	'q' = stack:b
	[mode b]
	DEFAULT = POP
	'q' = stack:b

# Version alpha8

Implement action filtering
	allow(A_UP)
	'q' = A_UP
	'w' = A_LEFT
	fk_translate(char *) -> char *
	"qw"		     -> A_UP

# Version alpha9

Implement group filtering
	To easy switching between filtered keys

# Version alpha10

Implement key direct input
	No more wait of <cr> of the key

# Version alpha11

Implement special combinate keys
	'<c>-q' = A_UP
	'<a>-q' = A_LEFT
	
# Version alpha12

Implement common combinate key
