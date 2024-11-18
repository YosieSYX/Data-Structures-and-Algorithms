class Node {
    Node next = null;
    int data;

    Node(int d) {
        this.data = d;
    }

    void insertInFront of this element(Node node, int d) {
        Node n = new Node(d);
        n.next = node;
        node = n;
    }
    
    void insertToTail(int d) {
        Node end = new Node(d);
        Node n = this;
        while (n.next != null) {
            n = n.next;
        }
        n.next = end;
    }

    //this is deleting a node with value n
    Node deleteNode(Node head, int d) {
        Node n = head;
        if(n.data == d) {
            return head.next;
        }
        while(n.next != null) {
            if (n.next.data == d) {
                n.next = n.next.next;
                return head;
            }
            n = n.next;
        }
        return head;
    }
}
