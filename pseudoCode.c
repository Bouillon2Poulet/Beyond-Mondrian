typedef struct {
    //Cube properties
    int x; //Position
    int y;
    int h; //Dimension
    int w;
} Cube;

typedef struct {
    //Map properties
    int width;
    int height;
    Cube tabDecor[20];

    //Children
    MapNode TLMapNode; //Top Left
    MapNode BLMapNode; //Bottom Left
    MapNode TRMapNode; //Top Right
    MapNode BRMapNode; //Bottom Right
} MapNode;

//Finding actual Node loop
MapNode actualNode = (MapNode)malloc(sizeof(MapNode))

while(actualNode.TLMapNode != NULL)
{
    if (player.x < (actualNode.width)/2)
    {
        if (player.y < (actualNode.height)/2)
        {
            actualNode=actualNode.TLMapNode;
        }
        else
        {
            actualNode=actualNode.BLMapNode;
        }
    }
    else
    {
        if (player.y < (actualNode.height)/2)
        {
            actualNode=actualNode.TRMapNode;
        }
        else
        {
            actualNode=actualNode.BRMapNode;
        }        
    }
}