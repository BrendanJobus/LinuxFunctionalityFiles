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
 * This class implements the competition using Dijkstra's algorithm
 */
import java.util.*;
import java.io.*;

public class CompetitionDijkstra {

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
		int dest;
		double dist;
		Path(int destination, double distance)
		{
			this.dest = destination;
			this.dist= distance;
		}
	}
	
	int slowestSpeed, maxSpeed;
	Vertex[] map;

    /**
     * @param filename: A filename containing the details of the city road network
     * @param sA: speed of contestant A
	 * @param sB: speed of contestant B
	 * @param sC: speed of contestant C
    */
    CompetitionDijkstra (String filename, int sA, int sB, int sC)
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
		
		for(int currentPath = 0; currentPath < map.length; currentPath++)
		{
			double[] distTo = new double[map.length];
			int hasEdgeTo[] = new int[map.length];			// used to make sure no vertex is isolated
			ArrayList<Integer> verticesToCheck = new ArrayList<Integer>();		// vertices that are currently connected to a
																				// vertex that is in the shortest path tree may
																				// be checked
			ArrayList<Integer> spt = new ArrayList<Integer>();				// vertices currently in the shortest path tree
			verticesToCheck.add(currentPath);
			
			for(int k = 0; k < hasEdgeTo.length; k++)
			{
				hasEdgeTo[k] = -1;
				distTo[k] = -1;
			}
			distTo[currentPath] = 0;
			hasEdgeTo[currentPath] = currentPath;
			
			while(!verticesToCheck.isEmpty())
			{
				int minIndex = minDist(verticesToCheck, distTo);
				int currentVertexNumber = verticesToCheck.remove(minIndex);
				Vertex currentVertex = map[currentVertexNumber];
				for(int j = 0; j < currentVertex.outgoingPaths.size(); j++)
				{
					Path path = currentVertex.outgoingPaths.get(j);
					if(path.dist + distTo[currentVertexNumber] < distTo[path.dest] || distTo[path.dest] == -1)
					{
						distTo[path.dest] = path.dist + distTo[currentVertexNumber];
						hasEdgeTo[path.dest] = currentVertexNumber;
					}
					if(!spt.contains(path.dest) && !verticesToCheck.contains(path.dest))
						verticesToCheck.add(path.dest);
				}
				spt.add(currentVertexNumber);
			}
			Arrays.sort(distTo);
			double longestDistance = distTo[distTo.length - 1];
			boolean isFullyConnected = true;
			for(int l = 0; l < hasEdgeTo.length; l++)
				if(hasEdgeTo[l] == -1)
					isFullyConnected = false;
			
			if(minimumTime == -1)
			{
				minimumTime = (longestDistance * 1000) / slowestSpeed;
			}
			else if(!isFullyConnected)
				return -1;
			else
				minimumTime = Math.max(minimumTime, (longestDistance * 1000) / slowestSpeed);
		}
		
		return (int)(Math.ceil(minimumTime));
    }
    
    public int minDist(ArrayList<Integer> vertices, double[] dist)
    {
         
        // Initialize min value 
    	int currentMin = 0;
    	for(int i = 0; i < vertices.size(); i++)
        {
        	if(dist[vertices.get(i)] < dist[vertices.get(currentMin)])
        		currentMin = i;
        }
        
    	return currentMin;
    }
}
