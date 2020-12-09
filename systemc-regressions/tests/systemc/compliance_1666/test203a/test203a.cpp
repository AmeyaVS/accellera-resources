#define SC_INCLUDE_DYNAMIC_PROCESSES

#include <systemc>
using namespace sc_core;
using namespace sc_dt;
using std::cout;
using std::endl;

// 3) Process handle methods, including invalid and terminated process

void invalid_handle_check(sc_process_handle& h)
{
  assert(h.valid() == false);
  assert(strcmp(h.name(), "") == 0);
  assert(h.proc_kind() == SC_NO_PROC_);
  assert(h.get_process_object() == 0);
  std::vector<sc_object*> children = h.get_child_objects();
  assert(children.size() == 0);
  assert(h.get_parent_object() == 0);
  assert(h.terminated() == false);
  assert(h.dynamic() == false);
  assert( !(h == h) );
  assert(h != h);
}

SC_MODULE(M)
{
  sc_in_clk clk;
  SC_CTOR(M)
  {
    sc_process_handle h;
    invalid_handle_check(h);

    SC_THREAD(T);
    SC_CTHREAD(CT, clk.pos());
    SC_METHOD(ME);

    sc_process_handle h3 = sc_spawn(sc_bind(&M::stat_thread, this), "stat_thread");
    sc_spawn_options opt;
    opt.spawn_method();
    sc_process_handle h4 = sc_spawn(sc_bind(&M::stat_method, this), "stat_method", &opt);

    std::vector<sc_object*> children = this->get_child_objects();
    assert(children.size() == 6);
  }
  void T()
  {
    sc_process_handle h;
    invalid_handle_check(h);

    sc_process_handle h2 = sc_get_current_process_handle();
    assert(h2.valid() == true);
    assert(strcmp(h2.name(), "top.m.T") == 0);
    assert(h2.proc_kind() == SC_THREAD_PROC_);
    assert(h2.get_process_object() != 0);
    std::vector<sc_object*> children2 = h2.get_child_objects();
    assert(children2.size() == 0);
    assert(h2.get_parent_object() == this);
    assert(h2.terminated() == false);
    assert(h2.dynamic() == false);
    assert(h2 == h2);
    assert(h2 != h);

    sc_process_handle h3 = sc_spawn(sc_bind(&M::dyn_thread, this), "dyn_thread");
    wait(1, SC_NS);

    if (h3.valid() == true)
    {
      assert(strcmp(h3.name(), "top.m.T.dyn_thread") == 0);
      assert(h3.proc_kind() == SC_THREAD_PROC_);
      assert(h3.get_process_object() != 0);
      std::vector<sc_object*> children3 = h3.get_child_objects();
      assert(children3.size() == 0);
      assert(h3.get_parent_object() == sc_get_current_process_handle().get_process_object());
      assert(h3.terminated() == true);
      assert(h3.dynamic() == true);
      assert(h3 == h3);
      assert( !(h3 != h3) );
    }

    sc_spawn_options opt;
    opt.spawn_method();
    sc_process_handle h4 = sc_spawn(sc_bind(&M::dyn_method, this), "dyn_method", &opt);
    assert(h4 != h3);

    wait(10, SC_NS);
    sc_stop();
  }

  void stat_thread()
  {
    sc_process_handle h;
    invalid_handle_check(h);

    wait(5, SC_NS);

    sc_process_handle h3 = sc_get_current_process_handle();
    assert(h3.valid() == true);
    assert(strcmp(h3.name(), "top.m.stat_thread") == 0);
    assert(h3.proc_kind() == SC_THREAD_PROC_);
    assert(h3.get_process_object() != 0);
    std::vector<sc_object*> children3 = h3.get_child_objects();
    assert(children3.size() == 0);
    assert(h3.get_parent_object() != 0);
    assert(h3.terminated() == false);
    assert(h3.dynamic() == false);
    assert(h3 == h3);
    assert(h3 != h);

    sc_process_handle h4;
    h4 = h3;
    assert(h4 == h3);
    assert(h4 != h);
  }

  void stat_method()
  {
    sc_process_handle h;
    invalid_handle_check(h);

    sc_process_handle h3 = sc_get_current_process_handle();
    assert(h3.valid() == true);
    assert(strcmp(h3.name(), "top.m.stat_method") == 0);
    assert(h3.proc_kind() == SC_METHOD_PROC_);
    assert(h3.get_process_object() != 0);
    std::vector<sc_object*> children3 = h3.get_child_objects();
    assert(children3.size() == 0);
    assert(h3.get_parent_object() != 0);
    assert(h3.terminated() == false);
    assert(h3.dynamic() == false);
    assert(h3 == h3);
    assert(h3 != h);

    sc_process_handle h4;
    h4 = h3;
    assert(h4 == h3);
    assert(h4 != h);
  }

  void dyn_thread()
  {
    sc_process_handle h;
    invalid_handle_check(h);

    sc_process_handle h3 = sc_get_current_process_handle();
    assert(h3.valid() == true);
    assert(strcmp(h3.name(), "top.m.T.dyn_thread") == 0);
    assert(h3.proc_kind() == SC_THREAD_PROC_);
    assert(h3.get_process_object() != 0);
    std::vector<sc_object*> children3 = h3.get_child_objects();
    assert(children3.size() == 0);
    assert(h3.get_parent_object() != 0);
    assert(h3.terminated() == false);
    assert(h3.dynamic() == true);
    assert(h3 == h3);
    assert(h3 != h);

    sc_process_handle h4(h3);
    assert(h4 == h3);
  }

  void dyn_method()
  {
    sc_process_handle h;
    invalid_handle_check(h);

    sc_process_handle h3 = sc_get_current_process_handle();
    assert(h3.valid() == true);
    assert(strcmp(h3.name(), "top.m.T.dyn_method") == 0);
    assert(h3.proc_kind() == SC_METHOD_PROC_);
    assert(h3.get_process_object() != 0);
    std::vector<sc_object*> children3 = h3.get_child_objects();
    assert(children3.size() == 0);
    assert(h3.get_parent_object() != 0);
    assert(h3.terminated() == false);
    assert(h3.dynamic() == true);
    assert(h3 == h3);
    assert(h3 != h);

    sc_process_handle h4(h3);
    assert(h4 == h3);
  }

  void CT()
  {
    sc_process_handle h;
    invalid_handle_check(h);

    sc_process_handle h2 = sc_get_current_process_handle();
    assert(h2.valid() == true);
    assert(strcmp(h2.name(), "top.m.CT") == 0);
    assert(h2.proc_kind() == SC_CTHREAD_PROC_);
    assert(h2.get_process_object() != 0);
    std::vector<sc_object*> children2 = h2.get_child_objects();
    assert(children2.size() == 0);
    assert(h2.get_parent_object() == this);
    assert(h2.terminated() == false);
    assert(h2.dynamic() == false);
    assert(h2 == h2);
    assert(h2 != h);
  }

  void ME()
  {
    sc_process_handle h;
    invalid_handle_check(h);

    sc_process_handle h2 = sc_get_current_process_handle();
    assert(h2.valid() == true);
    assert(strcmp(h2.name(), "top.m.ME") == 0);
    assert(h2.proc_kind() == SC_METHOD_PROC_);
    assert(h2.get_process_object() != 0);
    std::vector<sc_object*> children2 = h2.get_child_objects();
    assert(children2.size() == 0);
    assert(h2.get_parent_object() == this);
    assert(h2.terminated() == false);
    assert(h2.dynamic() == false);
    assert(h2 == h2);
    assert(h2 != h);
  }

};

struct Top: sc_module
{
  M *m;
  sc_clock clk;
  Top(sc_module_name)
  {
    m = new M("m");
    m->clk(clk);
  }
};

int sc_main(int argc, char* argv[])
{
  cout << "Should be silent" << endl;

  sc_process_handle h;
  invalid_handle_check(h);

  Top top("top");
  sc_start();

  cout << endl << "Success" << endl;
  return 0;
}
