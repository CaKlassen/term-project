#include "TileManager.h"

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: load
--
-- DATE: February 18, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: sf::FloatRect TileManager::load(std::string path)
--
-- RETURNS: sf::FloatRect - Returns null, needed for proper overloading 
--
-- NOTES:
-- Loads and populates the map with the contents of the
-- file at path
----------------------------------------------------------------------------------------------------------------------*/
sf::FloatRect* 
Manager::TileManager::load(std::string path)
{
    tset_.clear();
    tset_.open(path.c_str());
    if (tset_.fail() == true)
        throw "Map_Interpreter setfile() Exception: Could not open file";
    readtset();
    return NULL;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: get
--
-- DATE: February 18, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: sf::FloatRect TileManager::get(std::string rectId)
--
-- RETURNS: sf::FloatRect - Returns the appropriate rectangle
--
-- NOTES:
-- Uses a string id to get the id_resource to get the rectangle
----------------------------------------------------------------------------------------------------------------------*/
sf::FloatRect* 
Manager::TileManager::get(std::string rectId)
{
    return get(tsetmap_[rectId]);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getTexture
--
-- DATE: February 19, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire

--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: sf::Texture TileManager::getTexture()
--
-- RETURNS: sf::Texture - Returns the Texture
--
-- NOTES:
-- Returns the texture held.
----------------------------------------------------------------------------------------------------------------------*/
sf::Texture* 
Manager::TileManager::getTexture(id_resource id)
{
    return (textMgr.get(id));
}
/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: remove
--
-- DATE: February 18, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: sf::FloatRect TileManager::remove(std::string rectId)
--
-- RETURNS: void
--
-- NOTES:
-- Uses a string id to get the id_resource to remove the rectangle
----------------------------------------------------------------------------------------------------------------------*/
sf::FloatRect* 
Manager::TileManager::remove(std::string rectId)
{
    sf::FloatRect *rect = ResourceManager<sf::FloatRect*>::remove(tsetmap_[rectId]);
    tsetmap_.erase(rectId);
    return (rect);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: readtset
--
-- DATE: February 18, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: void TileManager::readtset()
--
-- RETURNS: void
--
-- NOTES:
-- Does the actual reading of the file.
----------------------------------------------------------------------------------------------------------------------*/
void 
Manager::TileManager::readtset()
{
    std::string dummy, texture, tilesize, tile, index;
    std::string id;
    std::set<std::string> tile_ids;
    float coords[4];
    id_resource value, texture_id;
    
    std::getline(tset_, dummy, ':'); // Remove 'texture:'
    std::getline(tset_, texture); // Extract file path
    std::getline(tset_, dummy); // Remove new line
    std::getline(tset_, dummy, ':'); // Remove 'tilesize:"
    std::getline(tset_, tilesize); // Extract tilesize
    std::getline(tset_, dummy); // Remove new line
    std::getline(tset_, dummy); // Remove 'tiles:(x,y,w,h)'
    
    texture_id = textMgr.store(textMgr_->load(texture));
    while (tset_.good() && tset_.eof() == false)
    {
        std::getline(tset_, index, ':');
        id = trim(index);
        
        std::getline(tset_, tile);
        if (tile.compare("end") == 0)
        {
            break;
        }
        
        tocords(tile, coords);
        value = store(new sf::FloatRect(coords[0], coords[1], coords[2], coords[3]));
        tsetmap_[id] = value;
        tile_ids.insert(id);
    }
    texturemap_[texture_id] = tile_ids;
    mapTexture = texture_id;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: trim
--
-- DATE: February 18, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: std::string TileManager::trim(std::string line)
--
-- RETURNS: std::string - The trimmed string
--
-- NOTES:
-- Trims leading and trailing whitespace from the given string 
-- and returns a copy.
----------------------------------------------------------------------------------------------------------------------*/
std::string
Manager::TileManager::trim(std::string line)
{
    std::string id = "";
    for (std::string::size_type i = 0; i < line.size(); i++)
    {
        if (!(isspace(line[i])))
        {
            id += line[i];
            break;
        }            
    }
    return id;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: tocords
--
-- DATE: February 18, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: void TileManager::tocords(std::string& tile, float *coords)
--
-- RETURNS: void
--
-- NOTES:
-- Changes the given string to an array of floats.
----------------------------------------------------------------------------------------------------------------------*/
void
Manager::TileManager::tocords(std::string& tile, float *coords)
{
    std::stringstream ss(tile);
    for (size_t i = 0; i < 4; i++)
    {
        ss >> coords[i];
    }
}


