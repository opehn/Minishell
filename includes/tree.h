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
