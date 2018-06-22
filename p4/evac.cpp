//nmcowan 
//Final Attempt 

#include <cstdlib>
#include "evac.h"
#include "EvacRunner.h"

using namespace std;

MyCity::MyCity() { }

MyCity::MyCity(const City *orig) 
{
 	ID = orig->ID;
	population = orig->population;
	evacuees = orig->evacuees;
	roadCount = orig->roadCount;
	roads = new MyRoad[orig->roadCount];

	for (int i = 0; i < orig->roadCount; i++)
		roads[i] = MyRoad(orig->roads[i], ID);

	isEvac = false;
}

MyRoad::MyRoad() { }

MyRoad::MyRoad(const Road orig, int from)
{
	ID = orig.ID;
	peoplePerHour = orig.peoplePerHour;
	toID = orig.destinationCityID;
	fromID = from;
	depth = -1;
	capacity = peoplePerHour;
}

inline bool MyRoad::operator> (const MyRoad& rhs)
{
	return ((depth > rhs.depth) || (depth == rhs.depth && capacity > rhs.capacity));
}

Evac::Evac(City *citie, int numCitie, int numRoads) : numCities(numCitie)
{
	numRoad = numRoads;

	numCities = numCitie;
	allCities = new MyCity[numCitie];

	roadCapacities = new int[numRoad * 2];
	roadPeople = new int[numRoad * 2];

	for (int i = 0; i < numCitie; i++)
		allCities[i] = MyCity(&citie[i]);

	totalEvacuees = 0;
	
	
	time = 1;

} 

inline bool MyRoad::operator< (const MyRoad& rhs)
{
	return ((depth < rhs.depth) || (depth == rhs.depth && capacity < rhs.capacity));
}




void Evac::evacuate(int *evacIDs, int numEvacs, EvacRoute *evacRoutes,
    int &routeCount)
{
	routeCount = 0;
	numEvacCities = numEvacs;

	for (int m = 0; m < numRoad * 2; m++)
	{
		roadCapacities[m] = -1;
		roadPeople[m] = -1;		
	}

	for (int i = 0; i < numEvacCities; i++)
	{
		allCities[evacIDs[i]].isEvac = true;
		allCities[evacIDs[i]].evacuees = allCities[evacIDs[i]].population;

		totalEvacuees += allCities[evacIDs[i]].population;
	}

	BFS(evacIDs);

	int RECURSE_DEPTH = 5; // NOTE changed!

//	int prev_total = totalEvacuees;

	while(totalEvacuees > 0) 
	{
//		prev_total = totalEvacuees;
		

		bool recurse_call = false;
		for (int i = 0; i < numEvacs; i++)
		{
			quicksort(allCities[evacIDs[i]].roads, 0, allCities[evacIDs[i]].roadCount - 1);
			for (int j = 0; j < allCities[evacIDs[i]].roadCount; j++)
			{
				if (allCities[evacIDs[i]].evacuees == 0 || roadCapacities[allCities[evacIDs[i]].roads[j].ID] == 0 || allCities[evacIDs[i]].roads[j].depth < 0)
					break;

				int taken = DFS(min2(allCities[evacIDs[i]].evacuees, roadCapacities[allCities[evacIDs[i]].roads[j].ID]), allCities[evacIDs[i]].roads[j], RECURSE_DEPTH - 1);
				allCities[evacIDs[i]].evacuees -= taken;
				totalEvacuees -= taken;
				if (taken > 0)
					recurse_call = true;
			}
		}

		bool anEvac = false;	
		for (int k = 0; k < numRoad * 2; k++)
		{
			if (roadCapacities[k] != -1 && roadCapacities[k] < roadPeople[k])
			{
				EvacRoute tmp;
				tmp.roadID = k;
				tmp.numPeople = roadPeople[k] - roadCapacities[k];
				tmp.time = time;

				evacRoutes[routeCount] = tmp;		
				routeCount++;

				roadCapacities[k] = roadPeople[k];
				anEvac = true;
			}
		}

		if (!anEvac)
		{
			EvacRoute tmp;
			tmp.roadID = 0;
			tmp.numPeople = 0;
			tmp.time = time;
			evacRoutes[routeCount] = tmp;
			routeCount++;
		}

		if (!recurse_call)
//		if (prev_total == totalEvacuees)
			RECURSE_DEPTH++;

		time++;

	} // while()

	numEvacCities = 0;

} 

void Evac::quicksort(MyRoad * array, int left, int right)
{
	int i = left; // left
	int j = right; // right
	MyRoad tmp;
	MyRoad pivot = array[(i + j) / 2];
	while (i <= j)
	{
		while ((array[i].depth > pivot.depth) || (array[i].depth == pivot.depth && roadCapacities[array[i].ID] > roadCapacities[pivot.ID]))
			i++;
		while ((array[j].depth < pivot.depth) || (array[j].depth == pivot.depth && roadCapacities[array[j].ID] < roadCapacities[pivot.ID]))
			j--;

		if (i <= j)
		{
			tmp = array[i];
			array[i] = array[j];
			array[j] = tmp;
			i++;
			j--;
		}
	}

	if (left < j)
		quicksort(array, left, j);
	if (i < right) 
		quicksort(array, i, right);
}

int Evac::DFS (int flow, MyRoad road, int recurse)
{
	if (recurse == 0)
		return 0; 

	int room = allCities[road.toID].population - allCities[road.toID].evacuees;
	int taken = 0; 
	if (room > 0 && !allCities[road.toID].isEvac)
	{
		taken = min(room, flow); 
		allCities[road.toID].evacuees += taken;
	}
	
		
	// quicksort roads
	quicksort(allCities[road.toID].roads, 0, allCities[road.toID].roadCount - 1);

	for (int i = 0; i < allCities[road.toID].roadCount; i++)
	{
		if (taken >= flow || allCities[road.toID].roads[i].depth < road.depth || roadCapacities[allCities[road.toID].roads[i].ID] == 0)
			break;
		
		taken += DFS(min(flow - taken, roadCapacities[allCities[road.toID].roads[i].ID]), allCities[road.toID].roads[i], recurse - 1);
		
	}

	// update capacity array
	roadCapacities[road.ID] -= taken;
		
	return taken;
}

void Evac::BFS (int * evacIDs)
{
	
	bool bfsVisited[numRoad*2];
	
	MyRoad allRoads[numRoad*2]; // NOTE: Changed!
	int roadArIndex = 0;

	for (int d = 0; d < numRoad*2; d++)
		bfsVisited[d] = false;

	for (int i = 0; i < numEvacCities; i++)
	{
		for (int j = 0; j < allCities[evacIDs[i]].roadCount; j++)
		{
//NOTE: changed!	if (!bfsVisited[allCities[evacIDs[i]].roads[j].ID])
//			{
				if (allCities[allCities[evacIDs[i]].roads[j].toID].isEvac)
					allCities[evacIDs[i]].roads[j].depth = 0;
				else
					allCities[evacIDs[i]].roads[j].depth = 1;

				allRoads[roadArIndex] = allCities[evacIDs[i]].roads[j];
				roadArIndex++;
				bfsVisited[allCities[evacIDs[i]].roads[j].ID] = true;


		}
	}
	
	int iter = 0;


	while (iter < roadArIndex)
	{
		MyRoad road = allRoads[iter];
		roadCapacities[road.ID] = road.capacity;		

		roadPeople[road.ID] = road.peoplePerHour;

		for (int k = 0; k < allCities[road.toID].roadCount; k++)
		{
			if (!bfsVisited[allCities[road.toID].roads[k].ID])
			{
				allCities[road.toID].roads[k].depth = road.depth + 1;
				allRoads[roadArIndex] = allCities[road.toID].roads[k];
				roadArIndex++;
				bfsVisited[allCities[road.toID].roads[k].ID] = true;

				if (allCities[road.toID].roads[k].ID % 2 == 0)
					bfsVisited[allCities[road.toID].roads[k].ID + 1] = true;
				else
					bfsVisited[allCities[road.toID].roads[k].ID - 1] = true;
			}
		}

		iter++;
	}

} 

int Evac::min2(int num1, int num2)
{
	if (num1 >= num2)
		return num2;

	return num1;
}