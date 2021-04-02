import static org.junit.Assert.*;
import org.junit.Test;

/*
 * 
 *  isolatedEWD.txt was added to test if my code successfully returned -1 if one of the vertices 
 *  wasn't connected to the rest
 *  
 *  My tests for the 1000EWD.txt file are separated and commented out as, even though they work on my
 *  machine, I was constantly getting errors when uploading that it would not compile the tests
 *  on this file.
 *  
 */

public class CompetitionTests {
		@Test
		 public void testDijkstra()
		 {
			CompetitionDijkstra d = new CompetitionDijkstra("tinyEWD.txt", 55, 75, 75);
			assertEquals(34, d.timeRequiredforCompetition());
			d = new CompetitionDijkstra("tinyEWD.txt", 10, 55, 55);
			assertEquals(-1, d.timeRequiredforCompetition());
			d = new CompetitionDijkstra("tinyEWD.txt", 55, 10, 55);
			assertEquals(-1, d.timeRequiredforCompetition());
			d = new CompetitionDijkstra("tinyEWD.txt", 55, 55, 10);
			assertEquals(-1, d.timeRequiredforCompetition());
			d = new CompetitionDijkstra("tinyEWD.txt", 110, 55, 55);
			assertEquals(-1, d.timeRequiredforCompetition());
			d = new CompetitionDijkstra("tinyEWD.txt", 55, 110, 55);
			assertEquals(-1, d.timeRequiredforCompetition());
			d = new CompetitionDijkstra("tinyEWD.txt", 55, 55, 110);
			assertEquals(-1, d.timeRequiredforCompetition());
			d = new CompetitionDijkstra(null, 55, 75, 75);
			assertEquals(-1, d.timeRequiredforCompetition()); 
			
			/*
			d = new CompetitionDijkstra("isolatedEWD.txt", 55, 75, 75);
			assertEquals(-1, d.timeRequiredforCompetition());
			*/
	 }

		@Test
		 public void testFW() 
		 {
			CompetitionFloydWarshall d = new CompetitionFloydWarshall("tinyEWD.txt", 55, 75, 75);
			assertEquals(34, d.timeRequiredforCompetition());
			d = new CompetitionFloydWarshall("", 55, 75, 75);
			assertEquals(-1, d.timeRequiredforCompetition());
			d = new CompetitionFloydWarshall("tinyEWD.txt", 10, 55, 55);
			assertEquals(-1, d.timeRequiredforCompetition());
			d = new CompetitionFloydWarshall("tinyEWD.txt", 55, 10, 55);
			assertEquals(-1, d.timeRequiredforCompetition());
			d = new CompetitionFloydWarshall("tinyEWD.txt", 55, 55, 10);
			assertEquals(-1, d.timeRequiredforCompetition());
			d = new CompetitionFloydWarshall("tinyEWD.txt", 110, 55, 55);
			assertEquals(-1, d.timeRequiredforCompetition());
			d = new CompetitionFloydWarshall("tinyEWD.txt", 55, 110, 55);
			assertEquals(-1, d.timeRequiredforCompetition());
			d = new CompetitionFloydWarshall("tinyEWD.txt", 55, 55, 110);
			assertEquals(-1, d.timeRequiredforCompetition());
			d = new CompetitionFloydWarshall(null, 55, 75, 75);
			assertEquals(-1, d.timeRequiredforCompetition());
			
			/*
			d = new CompetitionFloydWarshall("isolatedEWD.txt", 55, 75, 75);
			assertEquals(-1, d.timeRequiredforCompetition());
			*/
		}
		
		/*
		@Test
		public void test1000()
		{
			CompetitionDijkstra d = new CompetitionDijkstra("1000EWD.txt", 55, 75, 75);
			assertEquals(26, d.timeRequiredforCompetition());
			CompetitionFloydWarshall f = new CompetitionFloydWarshall("1000EWD.txt", 55, 75, 75);
			assertEquals(26, f.timeRequiredforCompetition());
		}
		*/
}