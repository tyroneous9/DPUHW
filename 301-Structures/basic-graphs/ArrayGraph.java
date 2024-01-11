package graphs;

import java.util.ArrayList;
import java.util.Collection;
import java.util.TreeMap;

public class ArrayGraph implements IndexedGraph
{
	private int numberOfEdges;
	private Collection<Integer>[] edges;
	private ArrayList<ArrayList<Integer>> vertices;
	
	@SuppressWarnings("unchecked")
	public ArrayGraph(int capacity)
	{
		numberOfEdges = 0;
		vertices = new ArrayList<ArrayList<Integer>>(capacity); 
		for(int i=0; i<capacity; i++) {
			vertices.add(new ArrayList<Integer>(capacity));
		}
	}

	@Override
	public int getNumberOfVerticies()
	{
		return vertices.size();
	}

	@Override
	public int getNumberOfEdges()
	{
		return numberOfEdges;
	}

	@Override
	public boolean addEdge(Integer from, Integer to)
	{
		if(!hasVertex(from) || !hasVertex(to)) {
			return false;
		}
		numberOfEdges += 1;
		vertices.get(from.intValue()).add(to);
		vertices.get(to.intValue()).add(from);
		return true;
	}

	@Override
	public Collection<Integer> getAdjacent(Integer to)
	{
		return vertices.get(to);
	}

	@Override
	public boolean removeEdge(Integer from, Integer to)
	{
		if(!hasVertex(from) || !hasVertex(to) || !vertices.get(from).contains(to)) {
			return false;
		}
		numberOfEdges -= 1;
		vertices.get(from.intValue()).remove(to);
		vertices.get(to.intValue()).remove(from);
		return true;
	}
	
	public boolean hasVertex(Integer vertex) {
		int capacity = getNumberOfVerticies()-1;
		if(vertex>capacity || vertex<0) {
			return false;
		}
		return true;
	}
}