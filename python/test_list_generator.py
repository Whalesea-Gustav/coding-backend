DomesticPlannerList = ['zixianwang', 'luciayin', 'v_bjpjzheng']
OverseaPlannerList = ['tarikxu', 'rosenzha', 'kccli']

_IsOversea = True

at_lists = OverseaPlannerList if _IsOversea else DomesticPlannerList
at_lists = ['<@{0}>'.format(planner) for planner in at_lists]



if __name__ == "__main__":
    print(''.join(at_lists))