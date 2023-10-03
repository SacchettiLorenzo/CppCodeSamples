#include "Simulation.h"


Simulation::Simulation(std::vector<Square>* vec_ptr, int* width, int* height, int* sqaresize, int* gap)
{
	this->setVecPtr(vec_ptr);
	this->width = width;
	this->height = height;
	this->sqauresize = sqaresize;
	this->gap = gap;
	

}

void Simulation::setVecPtr(std::vector<Square>* vec_ptr)
{
	this->vec_ptr = vec_ptr;
}

void Simulation::defineSquaredAround()
{
	simulativeSubset.clear();
	const int centerX = (*width / 2) / (*sqauresize + *gap);
	const int centerY = (*height / 2) / (*sqauresize + *gap);

	around.topLeftX = centerX;
	around.topLeftY = centerY;
	around.bottomRightX = centerX;
	around.bottomRightY = centerY;

	for (Square s : *vec_ptr) {
		if (s.getAliveStatus() == ALIVE) {
			if (s.GetGridPositionX() < around.topLeftX) around.topLeftX = s.GetGridPositionX();
			if (s.GetGridPositionY() < around.topLeftY) around.topLeftY = s.GetGridPositionY();
			if (s.GetGridPositionX() > around.bottomRightX) around.bottomRightX = s.GetGridPositionX();
			if (s.GetGridPositionY() > around.bottomRightY) around.bottomRightY = s.GetGridPositionY();
		}
	}

	if (around.topLeftX > 0)around.topLeftX--;
	if (around.topLeftY > 0)around.topLeftY--;

	if (around.topLeftX < *width)around.bottomRightX++;
	if (around.topLeftY < *height)around.bottomRightY++;

	std::cout << "around top Left X: " << around.topLeftX;
	std::cout << " around top Left Y: " << around.topLeftY << std:: endl;
	std::cout << "around bottom Right X: " << around.bottomRightX;
	std::cout << " around bottom Right Y: " << around.bottomRightY << std::endl;
	
	for (Square s : *vec_ptr) {
		if (s.GetGridPositionX() >= around.topLeftX && 
			s.GetGridPositionX() <= around.bottomRightX && 
			s.GetGridPositionY() >= around.topLeftY && 
			s.GetGridPositionY() <= around.bottomRightY) simulativeSubset.push_back(s);
	}
}

void Simulation::performSimulation()
{
	defineSquaredAround();
	for (Square s : simulativeSubset) {
		int counter = 0;
		
		if(s.GetGridPositionX() != around.topLeftX && s.GetGridPositionY() != around.topLeftY)counter+= checkTopLeftNeightbour( s);
		if (s.GetGridPositionX() != around.topLeftX)counter+= checkLeftNeightbour( s);
		if (s.GetGridPositionX() != around.topLeftX && s.GetGridPositionY() != around.bottomRightY)counter+= checkBottomLeftNeightbour( s);
		if(s.GetGridPositionY() != around.bottomRightY)counter+= checkBottomNeightbour( s);
		if(s.GetGridPositionX() != around.bottomRightX && s.GetGridPositionY() != around.bottomRightY)counter+= checkBottomRightNeightbour( s);
		if(s.GetGridPositionX() != around.bottomRightX)counter+= checkRightNeightbour( s);
		if (s.GetGridPositionX() != around.bottomRightX && s.GetGridPositionY() != around.topLeftY)counter+= checkTopRightNeightbour( s);
		if (s.GetGridPositionY() != around.topLeftY)counter+= checkTopNeightbour( s);

		
		if (s.getAliveStatus() == ALIVE) {
			if (counter < 2) s.SetAliveStatus(DEAD);
			//if(counter == 2 || counter == 3)s.SetAliveStatus(ALIVE);
			if (counter > 3) {
			s.SetAliveStatus(DEAD);
			}
		}else
		if (s.getAliveStatus() == DEAD) {
			if (counter == 3) s.SetAliveStatus(ALIVE);
		}

		std::vector<Square>::iterator it = std::find_if(this->vec_ptr->begin(), this->vec_ptr->end(), [s](Square q) {
			return q.GetGridPositionX() == s.GetGridPositionX() && q.GetGridPositionY() == s.GetGridPositionY();
			});

		*it = s;
	}


}

bool Simulation::checkTopLeftNeightbour(Square s)
{
	std::vector<Square>::iterator it = std::find_if(simulativeSubset.begin(), simulativeSubset.end(), [s](Square q) {
		return q.GetGridPositionX() == s.GetGridPositionX() - 1 && q.GetGridPositionY() == s.GetGridPositionY() - 1;
		});
	return it->getAliveStatus();
}

bool Simulation::checkLeftNeightbour(Square s)
{
	std::vector<Square>::iterator it = std::find_if(simulativeSubset.begin(), simulativeSubset.end(), [s](Square q) {
		return q.GetGridPositionX() == s.GetGridPositionX() - 1 && q.GetGridPositionY() == s.GetGridPositionY();
		});

	return it->getAliveStatus();
}

bool Simulation::checkBottomLeftNeightbour(Square s)
{
	std::vector<Square>::iterator it = std::find_if(simulativeSubset.begin(), simulativeSubset.end(), [s](Square q) {
		return q.GetGridPositionX() == s.GetGridPositionX() - 1 && q.GetGridPositionY() == s.GetGridPositionY() + 1;
		});

	return it->getAliveStatus();
}

bool Simulation::checkBottomNeightbour(Square s)
{
	std::vector<Square>::iterator it = std::find_if(simulativeSubset.begin(), simulativeSubset.end(), [s](Square q) {
		return q.GetGridPositionX() == s.GetGridPositionX() && q.GetGridPositionY() == s.GetGridPositionY() + 1;
		});

	return it->getAliveStatus();
}

bool Simulation::checkBottomRightNeightbour(Square s)
{
	std::vector<Square>::iterator it = std::find_if(simulativeSubset.begin(), simulativeSubset.end(), [s](Square q) {
		return q.GetGridPositionX() == s.GetGridPositionX() + 1 && q.GetGridPositionY() == s.GetGridPositionY() + 1;
		});

	return it->getAliveStatus();
}

bool Simulation::checkRightNeightbour(Square s)
{
	std::vector<Square>::iterator it = std::find_if(simulativeSubset.begin(), simulativeSubset.end(), [s](Square q) {
		return q.GetGridPositionX() == s.GetGridPositionX() + 1 && q.GetGridPositionY() == s.GetGridPositionY();
		});

	return it->getAliveStatus();
}

bool Simulation::checkTopRightNeightbour(Square s)
{
	std::vector<Square>::iterator it = std::find_if(simulativeSubset.begin(), simulativeSubset.end(), [s](Square q) {
		return q.GetGridPositionX() == s.GetGridPositionX() + 1 && q.GetGridPositionY() == s.GetGridPositionY() - 1;
		});

	return it->getAliveStatus();
}

bool Simulation::checkTopNeightbour(Square s)
{
	std::vector<Square>::iterator it = std::find_if(simulativeSubset.begin(), simulativeSubset.end(), [s](Square q) {
		return q.GetGridPositionX() == s.GetGridPositionX() && q.GetGridPositionY() == s.GetGridPositionY() - 1;
		});

	return it->getAliveStatus();
}
