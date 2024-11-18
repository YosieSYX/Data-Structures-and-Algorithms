class MinStack {
    private static class Node{
       int data;
       Node next;
       int min;
       private Node() {
       }

        private Node(int data) {
            this.data = data;
            this.min = data;
            this.next = null;
        }

        private Node(int data, int min) {
            this.data = data;
            this.min = min;
            this.next = null;
        }
    }
    
    Node top;
    public MinStack() {
        this.top = null;
    }

    public void push(int val) {
        Node newE;
        if (this.top == null) {
            this.top = new Node(val);
            //System.out.println(this.top.min);
            return;
        }
        if (val > this.top.min) {
            newE = new Node(val, this.top.min);
        }
        else {
            newE = new Node(val);
        }
        newE.next = this.top;
        this.top = newE;
        //System.out.println(this.top.min);
    }
    
    public void pop() {
        if (this.top == null) {
            return;
        }
        this.top = this.top.next;
    }
    
    public int top() {
        return this.top.data;
    }
    
    public int getMin() {
        return this.top.min;
    }
}

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(val);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */