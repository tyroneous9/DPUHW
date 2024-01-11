package trees;
import java.util.ArrayList;
import java.util.List;

@SuppressWarnings("rawtypes")
public class SimpleTreeSet implements SimpleSet
{
	Node root;
    class Node
    {
        Comparable<Object> value;
        Node left, right;
        int N=1;
        Node(Comparable<Object> value) {this.value = value;}
        public String toString() {return value.toString();} 
    }
    
    public int size()
    {
        return size(root);
    }
    
    public int size(Node curr) {
    	if(curr==null) {
    		return 0;
    	}
    	return curr.N;
    }
    
    
    public boolean isEmpty() 
    {
        return size()==0;
    }

    
    public void clear() 
    {
    	root = null;
    }

    
    public boolean contains(Comparable o) 
    {
    	if(get(o, root)!=null) {
    		return true;
    	}
        return false;
    }
    
    private Node get(Comparable o, Node curr) {
    	if(curr==null) {
    		return null;
    	}
    	int comparator = o.compareTo(curr.value);
    	if(comparator<0) {
    		curr = get(o,curr.left);
    	}
    	else if(comparator>0) {
    		curr = get(o,curr.right);
    	}
    	return curr;
    }

    public Object[] toArray() 
    {
        List<Object> returnMe = new ArrayList<Object>(size());
        fill(returnMe, 0, root);
        return returnMe.toArray();
    }
    
    private List<Object> fill(List<Object> lst, int i, Node curr) {
    	if(curr==null) {return lst;}
    	lst = fill(lst, i+1, curr.left);
    	lst.add(curr.value);
    	lst = fill(lst, i+1, curr.right);
    	return lst;
    }
    
    public boolean add(Comparable e) 
    {
    	int oldSize = size();
    	root = addHelper(e, root);
    	if(size()==oldSize) {return false;}
		return true;
    }

    private Node addHelper(Comparable e, Node curr) 
    {
    	if(curr==null) {
    		return new Node(e);
    	}
    	int comparator = e.compareTo(curr.value);
    	if(comparator<0) {
    		curr.left = addHelper(e, curr.left);
    	}
    	else if(comparator>0) {
    		curr.right = addHelper(e, curr.right);
    	}
    	else {
    		curr.value = e;
    	}
    	curr.N = size(curr.left)+size(curr.right)+1;
    	return curr;
    }

    public boolean remove(Comparable o) 
    {
    	int oldSize = size();
    	root = removeHelper(o, root);
    	if(size()==oldSize) {return false;}
		return true;
    }
    
    private Node removeHelper(Comparable o, Node curr) {
    	if(curr==null) {
    		return null;
    	}
    	int comparator = o.compareTo(curr.value);
    	if(comparator<0) {
    		curr.left = removeHelper(o,curr.left);
    	}
    	else if(comparator>0) {
    		curr.right = removeHelper(o,curr.right);
    	}
    	else {
    		if(curr.right==null) {
        		return curr.left;
        	}
    		if(curr.left==null) {
        		return curr.right;
        	}
        	Node removeMe = curr;
        	curr = getMin(removeMe.right);
        	curr.right = removeMin(removeMe.right);
        	curr.left = removeMe.left;
    	}
    	curr.N = size(curr.left)+size(curr.right)+1;
    	return curr;
    }
    
    private Node removeMin(Node curr) {
    	if(curr.left==null) {
    		return curr.right;
    	}
    	curr.left = removeMin(curr.left);
    	curr.N = size(curr.left)+size(curr.right)+1;
    	return curr;
    }
    
    public Node getMin(Node curr) {
    	if(curr.left==null) {
    		return curr;
    	}
    	return getMin(curr.left);
    }
    
    public int height()
	{
		if(size()==1 || isEmpty()) {
			return 0;
		}
		return heightHelper(root);
	}
	
	private int heightHelper(Node curr) {
		if(curr==null) {
			return -1;
		}
		int leftMax = heightHelper(curr.left);
        int rightMax = heightHelper(curr.right);
        return Math.max(leftMax, rightMax)+1;
	}
	
	public void printStructure()
	{
		printInOrder(root);
	}
	
	private Node printInOrder(Node curr) {
		if(curr.left!=null) {
			curr.left = printInOrder(curr.left);
		}
		System.out.println(curr.value+":"+size(curr));
		if(curr.right!=null) {
			curr.right = printInOrder(curr.right);
		}
		return curr;
	}
}