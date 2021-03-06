/*
 * A Contest to Meet (ACM) is a reality TV contest that sets three contestants at three random
 * city intersections. In order to win, the three contestants need all to meet at any intersection
 * of the city as fast as possible.
 * It should be clear that the contestants may arrive at the intersections at different times, in
 * which case, the first to arrive can wait until the others arrive.
 * From an estimated walking speed for each one of the three contestants, ACM wants to determine the
 * minimum time that a live TV broadcast should last to cover their journey regardless of the contestants’
 * initial positions and the intersection they finally meet. You are hired to help ACM answer this question.
 * You may assume the following:
 *     Each contestant walks at a given estimated speed.
 *     The city is a collection of intersections in which some pairs are connected by one-way
 * streets that the contestants can use to traverse the city.
 *
 * This class implements the competition using Floyd-Warshall algorithm
 */
import java.util.*;

import java.io.*;

public class CompetitionFloydWarshall {
	
	class Vertex 
	{
		ArrayList<Path> outgoingPaths;
		Vertex() 
		{
			outgoingPaths = new ArrayList<Path>();
		}
	}
	
	class Path 
	{
		int destination;
		double distance;
		Path(int destination, double distance)
		{
			this.destination = destination;
			this.distance = distance;
		}
	}
	
	int slowestSpeed, maxSpeed;
	Vertex[] map;

    /**
     * @param filename: A filename containing the details of the city road network
     * @param sA,       sB, sC: speeds for 3 contestants
     */
	CompetitionFloydWarshall(String filename, int sA, int sB, int sC) 
	{
		slowestSpeed = Math.min(sA, sB);
		slowestSpeed = Math.min(slowestSpeed, sC);
		maxSpeed = Math.max(sA, sB);
		maxSpeed = Math.max(maxSpeed, sC);
    	
		File file;
		if (filename != null)
			file = new File(filename);
		else
			file = null;
		try
		{
			BufferedReader br = new BufferedReader(new FileReader(file));
			String st = br.readLine();
			Scanner sc;
			int numberOfVertices = Integer.parseInt(st);
			map = new Vertex[numberOfVertices];
			for(int i = 0; i < map.length; i++)
			{
				map[i] = new Vertex();
			}
			st = br.readLine();

			while ((st = br.readLine()) != null)
			{
				sc = new Scanner(st);
				
				int start = Integer.parseInt(sc.next());
				int dest = Integer.parseInt(sc.next());
				double dist = Double.parseDouble(sc.next());
				map[start].outgoingPaths.add(new Path(dest, dist));
				
				sc.close();
			}
			br.close();
		} catch(Exception e) {
			map = new Vertex[0];
		}
    }


    /**
     * @return int: minimum minutes that will pass before the three contestants can meet
     */
	public int timeRequiredforCompetition()
	{
		double minimumTime = -1;
		if(slowestSpeed < 50)
			return -1;
		if(maxSpeed > 100)
			return -1;
		
		double dist[][] = createDist(map);
		for(int i = 0; i < dist.length; i++)
		{
			for(int j = 0; j < dist.length; j++)
			{
				for(int k = 0; k < dist.length; k++)
				{
					if(dist[j][i] + dist[i][k] < dist[j][k])
						dist[j][k] = dist[j][i] + dist[i][k];
				}
			}
		}
		double longestPath = longestPath(dist);
		if(longestPath == Double.MAX_VALUE || longestPath == -1)
			return -1;
		else
		{
			minimumTime = (longestPath * 1000) / slowestSpeed;
			return (int) (Math.ceil(minimumTime));
		}		
	}
	
	double[][] createDist(Vertex[] map)
	{
		double dist[][] = new double[map.length][map.length];
		for(int i = 0; i < dist.length; i++)
		{
			for(int j = 0; j < dist.length; j++)
			{
				if(i == j) 
					dist[i][j] = 0;
				else
					dist[i][j] = Double.MAX_VALUE;
			}
		}
		
		for(int i = 0; i < dist.length; i++)
		{
			int numberOfPaths = map[i].outgoingPaths.size();
			for(int j = 0; j < numberOfPaths; j++)
				dist[i][map[i].outgoingPaths.get(j).destination] = map[i].outgoingPaths.get(j).distance;
		}
		return dist;
	}
	

	double longestPath(double dist[][])
	{
		double worstCasePath = -1;
		for (int i = 0; i < dist.length; i++)
		{
			for (int j = 0; j < dist.length; j++)
			{
				if (dist[i][j] > worstCasePath)
					worstCasePath = dist[i][j];
			}
		}

		return worstCasePath;
	}
}