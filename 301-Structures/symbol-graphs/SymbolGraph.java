package graphs;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.Map;


public class SymbolGraph<E> implements Graph<E>
{
	private Map<E, List<E>> edges;
	private int numberOfEdges;
	
	public SymbolGraph()
	{
		numberOfEdges = 0;
		edges = new HashMap<E, List<E>>();
	}
	
	public boolean contains(E vertex) {
		return edges.containsKey(vertex);
	}
	
	public String toString() {
		return edges.toString();
	}
	
	public int getNumberOfVerticies()
	{
		return edges.size();
	}

	public int getNumberOfEdges()
	{
		return numberOfEdges;
	}

	public boolean addVertex(E value)
	{
		if(contains(value)) {
			return false;
		}
		edges.put(value, new ArrayList<E>());
		return true;
	}
	
	public boolean addEdge(E from, E to)
	{
		if(!contains(from) || !contains(to)) {
			return false;
		}
		numberOfEdges += 1;
		edges.get(from).add(to);
		edges.get(to).add(from);
		return true;
	}

	public Collection<E> getAdjacent(E to)
	{
		return edges.get(to);
	}

	public boolean removeEdge(E from, E to)
	{
		if(!contains(from) || !contains(to)) {
			return false;
		}
		numberOfEdges -= 1;
		edges.get(from).remove(to);
		edges.get(to).remove(from);
		return true;
	}
}