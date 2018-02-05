#include "Map.hpp"

Map::Map() : m_width(0), m_height(0)
{
    m_drawSolidMap = false;
    m_scale.x = 1;
    m_scale.y = 1;
}

void Map::loadFromeFolder(const std::string &path)
{

    if(!loadIndex(path))
    {
        std::cout << "Can't open map files. Aborting. \n";
        return;
    }


    int* layer0 = new int[m_width * m_height];
    int* layer1 = new int[m_width * m_height];
    int* layer2 = new int[m_width * m_height];

    loadLayer(0, path, layer0);
    loadLayer(1, path, layer1);
    loadLayer(2, path, layer2);

    m_layer0.load(m_tileset0, sf::Vector2u(TILE_SIZE, TILE_SIZE), layer0, m_width, m_height);
    m_layer1.load(m_tileset1, sf::Vector2u(TILE_SIZE, TILE_SIZE), layer1, m_width, m_height);
    m_layer2.load(m_tileset2, sf::Vector2u(TILE_SIZE, TILE_SIZE), layer2, m_width, m_height);

    delete [] layer0;
    delete [] layer1;
    delete [] layer2;

    std::vector<bool> solid(m_width * m_height);
    loadSolidMap(path, solid);
    m_solidMap.load(solid, m_width, m_height);


    std::cout << "===== Level Loaded ===== \n"
              << m_name + " by " + m_author + "\n"
              << "Dimension : " + std::to_string(m_width) + "x" + std::to_string(m_height) + "\n"
              //<< "Tilesets : " + t0 + ", " + t1 + ", " + t2 + "\n"
              << "========================\n" ;

}

/// layer MUST BE AN ARRAY M_WIDTH * M_HEIGHT
void Map::loadLayer(unsigned int layerNumber, const std::string &path, int* layer)
{
    std::string fullpath = path + "/layer" + std::to_string(layerNumber) + ".map";

    std::ifstream layer_f;
    layer_f.open(fullpath.c_str());

    char c;

    if(layer_f.is_open())
    {
        for(unsigned int i = 0; i < m_width * m_height; ++i)
        {
            std::string x;

            layer_f.get(c);
            while(c != ',')
            {
                if(c != '\n')
                {
                    x += c;
                }
                layer_f.get(c);
            }
            //std::cout << x << std::endl;

            std::istringstream(x) >> layer[i];
        }
    }
    layer_f.close();
}

void Map::loadSolidMap(const std::string &path, std::vector<bool> &solid)
{
    if(solid.size() != m_width * m_height)
        throw 2;

    std::string fullpath = path + "/solid.map";

    std::ifstream solid_f;
    solid_f.open(fullpath.c_str());

    char c;

    if(solid_f.is_open())
    {
        for(unsigned int i = 0; i < m_width * m_height; ++i)
        {
            std::string x;

            solid_f.get(c);
            while(c != ',')
            {
                if(c != '\n')
                {
                    x += c;
                }
                solid_f.get(c);
            }

            if(x[0] == '0')
                solid[i] = false;
            else
                solid[i] = true;
        }
    }

}

void Map::saveToFolder(const std::string &path)
{
    std::cout << path << "\n";


    if(_mkdir(path.c_str()) != 0)
    {
        std::cout << strerror(errno) << "\n";
    }

    std::string pathIndex  = path + "/info.txt";

    std::ofstream info_f;
    info_f.open(pathIndex.c_str(), std::ostream::trunc);

    info_f << m_name << '\n'  << m_author << '\n'
           << m_width << '\n' << m_height << '\n'
           << m_tileset0_path << '\n' << m_tileset1_path << '\n' << m_tileset2_path << '\n';

    info_f.close();

    saveLayer(path, 0);
    saveLayer(path, 1);
    saveLayer(path, 2);
    saveSolidMap(path);
}


void Map::setTile(unsigned int layer, sf::Vector2u coord, sf::Vector2u tilesetCoord)
{
    if(layer == 0)
        m_layer0.setTile(coord, tilesetCoord);
    else if(layer == 1)
        m_layer1.setTile(coord, tilesetCoord);
    else if(layer == 2)
        m_layer2.setTile(coord, tilesetCoord);
    else
        std::cout << "Invalid layer number in Map::setTile. Layer must be 0, 1 or 2. \n";
}

void Map::setTileSolid(unsigned int x, unsigned y, bool b)
{
    m_solidMap.setSolid(x, y, b);
}

bool Map::isTileSolid(unsigned int x, unsigned int y)
{
    return m_solidMap.isSolid(x, y);
}

Map Map::getEmptyMap(sf::Vector2u s, const std::string &path, const std::string &path_tm)
{
    Map res;

    res.manualLoad("Unnamed", "Unknown", s.x, s.y, path, path, path, path_tm);

    res.resetDimensions(s.x, s.y);

    return res;

}

bool Map::loadIndex(const std::string &path)
{
    std::string fullpath = path + "/info.txt";

    std::ifstream info_f;
    info_f.open(fullpath.c_str());

    std::string t0, t1, t2, w, h;

    if(info_f.is_open())
    {

        // Read level name
        std::getline(info_f, m_name);
        // Read author name
        std::getline(info_f, m_author);
        // Read level width
        std::getline(info_f, w);
        // Read level height
        std::getline(info_f, h);
        // Read layer0 tileset
        std::getline(info_f, t0);
        // Read layer1 tileset
        std::getline(info_f, t1);
        // Read layer2 tileset
        std::getline(info_f, t2);

        m_tileset0_path = t0;
        m_tileset1_path = t1;
        m_tileset2_path = t2;

        std::istringstream(w) >> m_width;
        std::istringstream(h) >> m_height;

        if (!m_tileset0.loadFromFile(t0))
            std::cout << "Unable to open layer0's tileset." << std::endl;

        if (!m_tileset1.loadFromFile(t1))
            std::cout << "Unable to open layer1's tileset." << std::endl;

        if (!m_tileset2.loadFromFile(t2))
            std::cout << "Unable to open layer2's tileset." << std::endl;

        info_f.close();
    }
    else
    {
        std::cout << "Unable to open map info file." << std::endl;
        return false;
    }
    return true;
}

void Map::resetDimensions(unsigned int w, unsigned int h)
{
    m_width = w;
    m_height = h;

    // Allocate arrays on the heap so that array's size is not restricted
    int* layer0 = new int[m_width * m_height];
    int* layer1 = new int[m_width * m_height];
    int* layer2 = new int[m_width * m_height];


    std::fill_n(layer0, m_width * m_height, 0);
    std::fill_n(layer1, m_width * m_height, 0);
    std::fill_n(layer2, m_width * m_height, 0);

    m_layer0.load(m_tileset0, sf::Vector2u(TILE_SIZE, TILE_SIZE), layer0, m_width, m_height);
    m_layer1.load(m_tileset1, sf::Vector2u(TILE_SIZE, TILE_SIZE), layer1, m_width, m_height);
    m_layer2.load(m_tileset2, sf::Vector2u(TILE_SIZE, TILE_SIZE), layer2, m_width, m_height);

    delete [] layer0;
    delete [] layer1;
    delete [] layer2;

    std::vector<bool> smap(m_width * m_height, 0);
    m_solidMap.load(smap, m_width, m_height);
}


void Map::manualLoad(const std::string &name, const std::string &author, unsigned int width, unsigned int height, const std::string &t0, const std::string &t1, const std::string &t2, const std::string &tm)
{
    m_name = name;
    m_author = author;
    m_width = width;
    m_height = height;

    m_tileset0_path = t0;
    m_tileset1_path = t1;
    m_tileset2_path = t2;

    std::vector<bool> smap(width * height, 0);
    m_solidMap.load(smap, width, height);

    if (!m_tileset0.loadFromFile(t0))
        std::cout << "Unable to open layer0's tileset." << std::endl;

    if (!m_tileset1.loadFromFile(t1))
        std::cout << "Unable to open layer1's tileset." << std::endl;

    if (!m_tileset2.loadFromFile(t2))
        std::cout << "Unable to open layer2's tileset." << std::endl;

    m_tsmask.loadMask(tm);


}

std::string Map::getName()
{
    return m_name;
}

void Map::saveLayer(const std::string &path, int layer)
{
    std::ofstream layer_f;
    std::string fullpath = path + "/layer" + std::to_string(layer) + ".map";

    layer_f.open(fullpath.c_str(), std::ostream::trunc);


    std::vector<int> layerArray;
    if(layer == 0)
        layerArray = m_layer0.getTileArray();
    else if(layer == 1)
        layerArray = m_layer1.getTileArray();
    else
        layerArray = m_layer2.getTileArray();

    for(unsigned int i = 0; i < layerArray.size(); ++i)
    {
        layer_f << layerArray[i] << ",";
        if(i != 0 && (i+1) % m_width == 0)
            layer_f << "\n";
    }
    layer_f.close();

}

void Map::saveSolidMap(const std::string &path)
{
    std::ofstream solid_f;
    std::string fullpath = path + "/solid.map";

    solid_f.open(fullpath.c_str(), std::ostream::trunc);

    for(unsigned int i = 0; i < m_width * m_height; ++i)
    {
        if(m_solidMap.isSolid(i))
                solid_f << "1" << ",";
            else
                solid_f << "0" << ",";

            if(i != 0 && (i+1) % m_width == 0)
                solid_f << "\n";

    }
    solid_f.close();
}

void Map::addOffset(int x, int y)
{
    m_viewOffset.x += x;
    m_viewOffset.y += y;

    //std::cout << m_viewOffset.x << ":" << m_viewOffset.y << "\n";
    //setPosition(getPosition().x - m_viewOffset.x, getPosition().y - m_viewOffset.y);
}

sf::Vector2f Map::getOffset()
{
    return m_viewOffset;
}

void Map::drawSolidMap(bool b)
{
    m_drawSolidMap = b;
}

bool Map::solidMapDrawed()
{
    if(m_drawSolidMap)
        return true;
    return false;
}

void Map::setName(std::string name)
{
    m_name = name;
}

void Map::setAuthor(std::string author)
{
    m_author = author;
}

void Map::setScale(float x, float y)
{
    m_scale.x = x;
    m_scale.y = y;
    m_layer0.setScale(x, y);
    m_layer1.setScale(x, y);
    m_layer2.setScale(x, y);
    m_solidMap.setScale(x, y);
}

void Map::setScale(sf::Vector2f s)
{
    m_scale = s;
    m_layer0.setScale(s);
    m_layer1.setScale(s);
    m_layer2.setScale(s);
    m_solidMap.setScale(s);
}

sf::Vector2f Map::getScale()
{
    return m_scale;
}

bool Map::isSolid(unsigned int x, unsigned int y)
{

}

