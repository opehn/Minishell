typedef enum e_token
{
    CMD = 0,
    OPT = 1,
    FD = 2,
    FNAME = 3,
    LEFT_RED = 4,
	RIGHD_RED = 5,
	LD_RED = 6,
	RD_RED = 7,
	LSQ = 8, //left single quote
	RSQ = 9, //right single quote
	LDQ = 10, //left double quote
	RDQ = 11, //right double quote
} t_token;


typedef enum e_nodetype
{
    PAIR_NODE = 12,
    CHAR_NODE = 13,
} t_nodetype;

typedef struct s_node t_node;

typedef struct s_pairvalue
{
    t_node *left;
    t_node *right;
} t_pairvalue;

typedef char t_charvalue;

typedef union u_nodevalue
{
    t_pairvalue pair;
    t_charvalue value;
} t_nodevalue;

struct s_node
{
    t_nodetype      type; //enum
    t_nodevalue     data; //union
};
